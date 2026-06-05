#!/usr/bin/env python3
import os, sys, json, time, logging, argparse, requests
from datetime import timedelta
from urllib.parse import urlparse, urljoin
from bs4 import BeautifulSoup

# ——— Configurações de sessão ———
USER_AGENT = (
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
    "AppleWebKit/537.36 (KHTML, like Gecko) "
    "Chrome/114.0.0.0 Safari/537.36"
)

# ——— Logging ———
def setup_logging():
    os.makedirs('logs', exist_ok=True)
    log = logging.getLogger(); log.setLevel(logging.INFO)

    fh = logging.FileHandler('logs/download_episodes.log', encoding='utf-8')
    fh.setLevel(logging.INFO)
    fh.setFormatter(logging.Formatter('%(asctime)s %(levelname)s: %(message)s'))
    log.addHandler(fh)

    eh = logging.FileHandler('logs/error.log', encoding='utf-8')
    eh.setLevel(logging.ERROR)
    eh.setFormatter(logging.Formatter('%(asctime)s %(levelname)s: %(message)s'))
    log.addHandler(eh)

    ch = logging.StreamHandler(sys.stdout)
    ch.setLevel(logging.INFO)
    ch.setFormatter(logging.Formatter('[%(asctime)s] %(message)s', datefmt='%H:%M:%S'))
    log.addHandler(ch)

# ——— Download em streaming com progresso ———
def download_file_stream(url, dest, session):
    with session.get(url, stream=True) as r:
        r.raise_for_status()
        total = int(r.headers.get('Content-Length', 0))
        start = time.time()
        done = 0
        chunk = 32_768
        with open(dest, 'wb') as f:
            for buf in r.iter_content(chunk):
                if not buf: continue
                f.write(buf); done += len(buf)
                elapsed = time.time() - start
                pct = done/total*100 if total else 0
                sp = done/elapsed if elapsed>0 else 0
                eta = (total-done)/sp if sp>0 else 0
                sys.stdout.write(
                    f"\r  ↓ {os.path.basename(dest):30.30} "
                    f"{pct:6.2f}% | {done//1024:7d}/{total//1024:7d} KB | "
                    f"{(sp/1024):6.2f} KB/s | ETA {str(timedelta(seconds=int(eta)))}"
                )
                sys.stdout.flush()
        print()

# ——— Baixa um episódio via link “Baixar” ———
def download_episode(page_url, out_dir, session):
    logging.info(f"  → Acessando {page_url}")
    resp = session.get(page_url)
    resp.raise_for_status()
    soup = BeautifulSoup(resp.text, 'html.parser')

    # procura o botão “Baixar” na página :contentReference[oaicite:5]{index=5}
    a = soup.find('a', class_='btn-down')
    if not a or not a.get('href'):
        raise RuntimeError("Botão de download não encontrado na página.")
    dl_url = urljoin(page_url, a['href'])
    logging.info(f"    → Download link: {dl_url}")

    # segue o redirect e baixa o ficheiro
    with session.get(dl_url, stream=True) as r:
        r.raise_for_status()
        # determina nome pelo Content-Disposition ou URL final
        cd = r.headers.get('Content-Disposition','')
        if 'filename=' in cd:
            fname = cd.split('filename=')[-1].strip(' "\'')
        else:
            ext = os.path.splitext(r.url)[1] or '.mp4'
            fname = f"{os.path.basename(page_url)}{ext}"
        dest = os.path.join(out_dir, fname)
        logging.info(f"    ↓ Salvando como: {dest}")
        # reusa nossa função de progresso
        download_file_stream(r.url, dest, session)
        logging.info(f"    ✓ Episódio salvo: {fname}")

# ——— Processa cada bloco de episódios ———
def download_anime(entry, base_dir, session):
    url   = entry['url'].rstrip('/')
    first = int(entry['first'])
    last  = int(entry['last'])
    slug  = os.path.basename(urlparse(url).path)
    out   = entry.get('output') or os.path.join(base_dir, slug)
    os.makedirs(out, exist_ok=True)

    logging.info(f"\nBaixando {slug}: ep. {first:02d} → {last:02d} em {out}")
    for ep in range(first, last+1):
        ep_str = f"{ep:02d}"
        page   = f"{url}/episodio-{ep_str}"
        try:
            download_episode(page, out, session)
        except Exception as e:
            logging.error(f"    ✗ Erro ep. {ep_str}: {e}", exc_info=True)

# ——— Entrypoint ———
def main():
    setup_logging()
    parser = argparse.ArgumentParser(
        description="Baixa faixas de episódios de animes do BetterAnime usando o botão de download."
    )
    parser.add_argument(
        '-j','--json',
        default='anime.json',
        help='Arquivo JSON com lista de animes: [{url,first,last[,output]},…]'
    )
    parser.add_argument(
        '-b','--base-dir',
        default='C:\\anime_download',
        help='Diretório-base (default: C:\\anime_download\\)'
    )
    args = parser.parse_args()

    try:
        with open(args.json, encoding='utf-8') as f:
            data = json.load(f)
    except Exception as e:
        logging.error(f"Falha ao ler {args.json}: {e}")
        sys.exit(1)

    session = requests.Session()
    session.headers.update({'User-Agent': USER_AGENT})

    for idx, entry in enumerate(data, 1):
        if all(k in entry for k in ('url','first','last')):
            download_anime(entry, args.base_dir, session)
        else:
            logging.warning(f"Ignorando entrada inválida #{idx}: {entry}")

if __name__ == '__main__':
    main()
