
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import time
import json
import argparse
import logging
from datetime import timedelta
from yt_dlp import YoutubeDL

class DownloadManager:
    def __init__(self, total_videos):
        self.total_videos = total_videos
        self.overall_start = None
        self.video_start_times = {}
        self.video_durations = []
        self.completed = 0

    def progress_hook(self, d):
        status = d.get('status')
        filename = os.path.basename(d.get('filename', ''))
        now = time.time()

        if self.overall_start is None:
            self.overall_start = now

        if status == 'downloading':
            if filename not in self.video_start_times:
                self.video_start_times[filename] = now

            percent = d.get('_percent_str', '').strip()
            speed   = d.get('_speed_str', '').strip()
            eta     = d.get('_eta_str', '').strip()

            elapsed_overall = now - self.overall_start
            avg = (sum(self.video_durations) / len(self.video_durations)) if self.video_durations else None
            left = self.total_videos - self.completed - 1
            eta_global = str(timedelta(seconds=int(avg*left))) if avg else '??:??:??'

            sys.stdout.write(
                f"\r[{time.strftime('%H:%M:%S')}] "
                f"{self.completed+1}/{self.total_videos} | {percent} @ {speed} "
                f"| ETA vídeo: {eta} | ETA total: {eta_global}"
            )
            sys.stdout.flush()

        elif status == 'finished':
            start = self.video_start_times.pop(filename, now)
            dur = now - start
            self.video_durations.append(dur)
            self.completed += 1
            print()  # nova linha
            logging.info(
                f"Concluído {self.completed}/{self.total_videos}: "
                f"{filename} (tempo: {timedelta(seconds=int(dur))})"
            )

    def error(self, msg):   logging.error(msg)
    def warning(self, msg): logging.warning(msg)
    def debug(self, msg):   logging.debug(msg)
    def info(self, msg):    logging.info(msg)

def setup_logging():
    os.makedirs('logs', exist_ok=True)
    lg = logging.getLogger()
    lg.setLevel(logging.INFO)

    fh = logging.FileHandler('logs/download_playlist.log', encoding='utf-8')
    fh.setLevel(logging.INFO)
    fh.setFormatter(logging.Formatter('%(asctime)s %(levelname)s: %(message)s'))
    lg.addHandler(fh)

    eh = logging.FileHandler('logs/error.log', encoding='utf-8')
    eh.setLevel(logging.ERROR)
    eh.setFormatter(logging.Formatter('%(asctime)s %(levelname)s: %(message)s'))
    lg.addHandler(eh)

    ch = logging.StreamHandler(sys.stdout)
    ch.setLevel(logging.INFO)
    ch.setFormatter(logging.Formatter('[%(asctime)s] %(message)s', datefmt='%H:%M:%S'))
    lg.addHandler(ch)

def download_one(playlist_url: str, output_dir: str, cookiefile: str):
    # Primeiro, obtemos só as entradas para contar
    temp_opts = {'quiet': True, 'extract_flat': True, 'cookiefile': cookiefile}
    with YoutubeDL(temp_opts) as ydl:
        info = ydl.extract_info(playlist_url, download=False)
    entries = info.get('entries') or []
    total = len(entries)

    dm = DownloadManager(total)
    os.makedirs(output_dir, exist_ok=True)
    logging.info(f"--> Iniciando ({total} vídeos): {playlist_url}")
    logging.info(f"    saída em: {output_dir}")

    ydl_opts = {
        'format': 'bv*+ba/b',
        'merge_output_format': 'mkv',
        'yes_playlist': True,
        'outtmpl': os.path.join(output_dir, '%(playlist_index)03d - %(title).100s.%(ext)s'),
        'progress_hooks': [dm.progress_hook],
        'logger': dm,
        'quiet': True,
        'cookiefile': cookiefile,
    }
    with YoutubeDL(ydl_opts) as ydl:
        ydl.download([playlist_url])

    logging.info(f"<-- Concluído playlist: {playlist_url}\n")

def main():
    setup_logging()
    parser = argparse.ArgumentParser(
        description='Baixa várias playlists do YouTube listadas em JSON, com suporte a cookies.'
    )
    parser.add_argument('-j','--json',       default='url.json',
                        help='Ficheiro JSON com lista de playlists (default: url.json)')
    parser.add_argument('-d','--default-dir',default='downloaded_pl',
                        help='Diretório-base para playlists (default: ./downloaded_pl/)')
    parser.add_argument('-c','--cookies',    default='cookies.txt',
                        help='Ficheiro de cookies exportado do browser (default: cookies.txt)')
    args = parser.parse_args()

    # carrega JSON
    try:
        with open(args.json, encoding='utf-8') as f:
            data = json.load(f)
    except Exception as e:
        logging.error(f"Não foi possível ler {args.json}: {e}")
        sys.exit(1)

    if not isinstance(data, list) or not data:
        logging.error("O JSON precisa ser uma lista não-vazia de URLs ou objetos.")
        sys.exit(1)

    for idx, item in enumerate(data, 1):
        if isinstance(item, str):
            url = item
            out = os.path.join(args.default_dir, f'playlist_{idx:02d}')
        elif isinstance(item, dict) and 'url' in item:
            url = item['url']
            out = item.get('output') or os.path.join(args.default_dir, f'playlist_{idx:02d}')
        else:
            logging.warning(f"Ignorando entrada inválida na posição {idx}: {item}")
            continue

        try:
            download_one(url, out, args.cookies)
        except Exception:
            logging.exception(f"Erro ao processar playlist #{idx}: {url}")

if __name__ == '__main__':
    main()
