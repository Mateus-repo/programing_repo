#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
download_animes.py

Descarrega episódios de BetterAnime em MKV na melhor qualidade,
usando Playwright + yt-dlp para extrair o URL real de cada episódio.

1) Lista eps (all ou intervalo)
2) Playwright headless descobre HLS/MP4 real
3) yt-dlp extrai tamanho total
4) Download paralelo com progresso (Rich)
"""

import os
import sys
import json
import argparse
import logging
import asyncio
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor

import requests
from bs4 import BeautifulSoup
from yt_dlp import YoutubeDL
from rich.progress import (
    Progress,
    TextColumn,
    DownloadColumn,
    TransferSpeedColumn,
    TimeRemainingColumn,
)
from rich.console import Console
from playwright.async_api import async_playwright

# ─── Configuração de logs e console ────────────────────────────────────────────
console = Console()
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    handlers=[
        logging.FileHandler("download_animes.log", encoding="utf-8"),
        logging.StreamHandler(sys.stdout),
    ],
)
logger = logging.getLogger("anime_downloader")

HEADERS = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"}


# ─── Carrega anime.json ─────────────────────────────────────────────────────────
def load_config(fp: Path):
    if not fp.exists():
        logger.error(f"Config não encontrada: {fp}")
        sys.exit(1)
    try:
        return json.loads(fp.read_text("utf-8"))
    except Exception as e:
        logger.error(f"Erro a ler JSON: {e}")
        sys.exit(1)


# ─── Raspa todos os eps da página principal ───────────────────────────────────
def list_all_eps(main_url: str):
    r = requests.get(main_url, headers=HEADERS, timeout=15)
    r.raise_for_status()
    soup = BeautifulSoup(r.text, "html.parser")
    anchors = soup.select("ul.episodios-list a, .episodes-list a, .episodios a")
    eps = []
    for a in anchors:
        href = a.get("href")
        if not href:
            continue
        title = a.text.strip() or href.split("/")[-1]
        if href.startswith("/"):
            href = "https://betteranime.net" + href
        eps.append((title, href))
    return eps


# ─── Usa Playwright para descobrir HLS/MP4 real ─────────────────────────────────
async def discover_stream_urls(eps):
    """
    Recebe lista de (title, page_url) e devolve lista de (title, media_url).
    """
    out = []
    async with async_playwright() as pw:
        browser = await pw.chromium.launch(headless=True)
        for title, page_url in eps:
            await asyncio.sleep(0.1)  # throttle ligeiro
            page = await browser.new_page()
            await page.set_extra_http_headers(HEADERS)
            try:
                await page.goto(page_url, wait_until="domcontentloaded", timeout=60000)
                # tenta extrair via JWPlayer API
                files = await page.evaluate(
                    """() => {
                         if (window.jwplayer) {
                           const cfg = jwplayer("player").getConfig();
                           if (cfg && cfg.sources) {
                             return cfg.sources.map(s => s.file);
                           }
                         }
                         return [];
                       }"""
                )
            except Exception:
                files = []
            # fallback: regex no HTML
            if not files:
                html = await page.content()
                import re

                files = re.findall(
                    r'https?://[^\s\'"]+\.m3u8[^\s\'"]*', html
                ) + re.findall(
                    r'https?://[^\s\'"]+\.mp4[^\s\'"]*', html
                )
            # escolhe HLS primeiro
            chosen = next((u for u in files if u.endswith(".m3u8")), None)
            if not chosen and files:
                chosen = files[0]
            if chosen:
                out.append((title, chosen))
                logger.info(f"[discover] {title} → {chosen.split('?')[0]}")
            else:
                logger.error(f"[discover] falhou {title}")
            await page.close()
        await browser.close()
    return out


# ─── Hook para atualizar Rich Progress ──────────────────────────────────────────
def make_hook(prog: Progress, task_id: int):
    def hook(d):
        if d.get("status") == "downloading":
            total = d.get("total_bytes") or d.get("total_bytes_estimate") or 0
            done = d.get("downloaded_bytes", 0)
            if total:
                prog.update(task_id, total=total)
            prog.update(task_id, completed=done)
    return hook


# ─── Extrai tamanho e descarrega ───────────────────────────────────────────────
def download_all(eps_media, out_folder: Path):
    # 1) extrai tamanhos
    ydl_info = {
        "quiet": True,
        "skip_download": True,
        "no_warnings": True,
        "format": "bestvideo+bestaudio/best",
        "merge_output_format": "mkv",
    }
    total = 0
    with YoutubeDL(ydl_info) as ydl:
        for title, murl in eps_media:
            try:
                info = ydl.extract_info(murl, download=False)
                sz = info.get("filesize") or info.get("filesize_approx") or 0
                total += sz
            except Exception as e:
                logger.warning(f"[size] {title} falhou: {e}")

    console.print(f"\n[bold]Tamanho estimado:[/] {total/1024**2:.2f} MB\n")

    # 2) barra de progresso
    prog = Progress(
        TextColumn("{task.description}"),
        DownloadColumn(),
        TransferSpeedColumn(),
        TimeRemainingColumn(),
        console=console,
    )
    overall = prog.add_task("[green]Total", total=total)

    ydl_base = {
        **ydl_info,
        "http_headers": {"Referer": "https://betteranime.net"},
        "logger": logger,
    }

    def dl_job(item):
        title, murl = item
        out = out_folder / f"{title}.mkv"
        out.parent.mkdir(parents=True, exist_ok=True)
        opts = dict(ydl_base, outtmpl=str(out))
        tid = prog.add_task(f"▶ {title}", total=None)
        opts["progress_hooks"] = [
            make_hook(prog, tid),
            make_hook(prog, overall),
        ]
        try:
            with YoutubeDL(opts) as ydl:
                ydl.download([murl])
        except Exception as e:
            logger.error(f"[dl] {title} erro: {e}")
        finally:
            prog.remove_task(tid)

    # 3) executa em paralelo
    with prog:
        with ThreadPoolExecutor(max_workers=4) as ex:
            for item in eps_media:
                ex.submit(dl_job, item)


# ─── Pipeline completo por anime ───────────────────────────────────────────────
async def run_anime(anime, base_out: Path):
    url = anime["url"].rstrip("/")
    first, last = anime.get("first"), anime.get("last")
    slug = url.split("/")[-1]
    folder = base_out / slug
    folder.mkdir(parents=True, exist_ok=True)
    console.rule(f"[bold cyan]{slug}")

    # decide lista de episódios
    if first == "all":
        eps = list_all_eps(url)
    else:
        try:
            f, l = int(first), int(last)
            eps = [(f"ep-{n:02d}", f"{url}/episodio-{n:02d}") for n in range(f, l + 1)]
        except:
            logger.warning(f"[{slug}] intervalo inválido, raspando tudo…")
            eps = list_all_eps(url)

    logger.info(f"[{slug}] {len(eps)} episódios encontrados")

    eps_media = await discover_stream_urls(eps)
    download_all(eps_media, folder)


# ─── Async runner ─────────────────────────────────────────────────────────────
async def run_all(cfg, base_out: Path):
    await asyncio.gather(*(run_anime(a, base_out) for a in cfg))


# ─── Main ─────────────────────────────────────────────────────────────────────
def main():
    p = argparse.ArgumentParser(
        description="Descarrega BetterAnime em MKV (melhor qualidade)."
    )
    p.add_argument(
        "-c", "--config", type=Path, default=Path("anime.json"),
        help="Ficheiro JSON (default: anime.json)"
    )
    p.add_argument(
        "-o", "--out", type=Path,
        help="Pasta destino (default: C:/anime_download ou ~/anime_download)"
    )
    args = p.parse_args()

    base_out = (
        args.out
        if args.out
        else Path("C:/anime_download") if os.name == "nt"
        else Path.home() / "anime_download"
    )
    base_out.mkdir(parents=True, exist_ok=True)

    cfg = load_config(args.config)
    logger.info(f"⇢ iniciando {len(cfg)} anime(s) em {base_out}")

    asyncio.run(run_all(cfg, base_out))

    logger.info("✅ todos concluídos")


if __name__ == "__main__":
    main()
