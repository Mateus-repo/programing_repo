import json
import sys
from yt_dlp import YoutubeDL

def load_urls(json_path):
    with open(json_path, 'r', encoding='utf-8') as f:
        data = json.load(f)
    if isinstance(data, dict) and "urls" in data:
        return data["urls"]
    if isinstance(data, list):
        return data
    raise ValueError("Formato de JSON inválido. Use lista ou objeto com chave 'urls'.")

def download_best_audio(url, template):
    opts = {
        'format': 'bestaudio/best',
        'outtmpl': template or '%(title)s.%(ext)s',
        'postprocessors': [{
            'key': 'FFmpegExtractAudio',
            'preferredcodec': 'mp3',
            'preferredquality': '320',
        }],
        'noplaylist': False,  # para que baixe playlists completas
        'quiet': False
    }
    with YoutubeDL(opts) as ydl:
        ydl.download([url])

def main():
    # Recebe: [json_file] [template_saida]
    json_file = sys.argv[1] if len(sys.argv) > 1 else 'url.json'
    template   = sys.argv[2] if len(sys.argv) > 2 else None

    try:
        urls = load_urls(json_file)
    except Exception as e:
        print(f"Erro ao ler '{json_file}': {e}")
        sys.exit(1)

    for link in urls:
        print(f"\nIniciando download de: {link}")
        download_best_audio(link, template)

if __name__ == '__main__':
    main()
