import os
import json
import re
import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
from yt_dlp import YoutubeDL

def load_json(file_path):
    """Carrega o conteúdo de um arquivo JSON e retorna os dados."""
    if not os.path.isfile(file_path):
        print(f"Arquivo {file_path} não encontrado.")
        exit(1)
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            return json.load(f)
    except Exception as e:
        print(f"Erro ao carregar {file_path}: {e}")
        exit(1)

# Carregar as credenciais do Spotify a partir de spotify.json.
creds = load_json("spotify.json")
client_id = creds.get("client_id")
client_secret = creds.get("client_secret")
redirect_uri = creds.get("redirect_uri")

if not client_id or not client_secret or not redirect_uri:
    print("Verifique se 'spotify.json' contém as chaves 'client_id', 'client_secret' e 'redirect_uri'.")
    exit(1)

# Configurar as variáveis de ambiente para o Spotipy (essa abordagem é opcional,
# pois também podemos passar os parâmetros diretamente ao SpotifyClientCredentials)
os.environ["SPOTIPY_CLIENT_ID"] = client_id
os.environ["SPOTIPY_CLIENT_SECRET"] = client_secret
os.environ["SPOTIPY_REDIRECT_URI"] = redirect_uri

def create_output_directory(directory="dwYt"):
    """Cria a pasta de saída, se não existir."""
    if not os.path.exists(directory):
        os.makedirs(directory)
    return directory

def sanitize_filename(text):
    """Remove caracteres inadequados para nomes de arquivos."""
    return "".join(c for c in text if c.isalnum() or c in " -_").rstrip()

def get_spotify_playlist_tracks(playlist_url):
    """
    Extrai o ID da playlist do Spotify a partir do URL e retorna uma lista de tuplas (título, artistas).
    """
    pattern = r"playlist/([a-zA-Z0-9]+)"
    match = re.search(pattern, playlist_url)
    if not match:
        raise Exception("Não foi possível extrair o ID da playlist a partir do URL fornecido.")
    playlist_id = match.group(1)

    sp = spotipy.Spotify(auth_manager=SpotifyClientCredentials())
    tracks = []
    results = sp.playlist_items(playlist_id)
    tracks.extend(results['items'])
    
    # Trata a paginação caso haja muitas faixas
    while results.get('next'):
        results = sp.next(results)
        tracks.extend(results['items'])
    
    track_infos = []
    for item in tracks:
        track = item.get('track')
        if track is None:
            continue
        title = track.get('name')
        artists = ", ".join(artist.get('name') for artist in track.get('artists', []))
        track_infos.append((title, artists))
    
    return track_infos

def download_track_youtube(query, output_directory="dwYt"):
    """
    Usa o yt-dlp para buscar e baixar o áudio do YouTube, convertendo-o para MP3.
    """
    ydl_opts = {
        'format': 'bestaudio/best',
        'outtmpl': os.path.join(output_directory, sanitize_filename(query) + '.%(ext)s'),
        'postprocessors': [{
            'key': 'FFmpegExtractAudio',
            'preferredcodec': 'mp3',
            'preferredquality': '192',
        }],
        'ignoreerrors': True,
        'quiet': True,
        'noplaylist': True,
    }
    
    # O prefixo "ytsearch1:" instrui o yt-dlp a buscar e usar o primeiro resultado encontrado
    search_query = f"ytsearch1:{query}"
    with YoutubeDL(ydl_opts) as ydl:
        try:
            ydl.download([search_query])
        except Exception as e:
            print(f"Erro ao baixar '{query}': {e}")

if __name__ == "__main__":
    # Carrega a URL da playlist a partir do arquivo url.json
    data = load_json("url.json")
    playlist_url = data.get("url")
    if not playlist_url:
        print("O arquivo 'url.json' precisa conter a chave 'url' com o link da playlist do Spotify.")
        exit(1)

    output_dir = create_output_directory("dwYt")
    print(f"Obtendo músicas da playlist: {playlist_url}")
    
    try:
        track_list = get_spotify_playlist_tracks(playlist_url)
    except Exception as e:
        print("Erro ao obter músicas da playlist:", e)
        exit(1)
    
    print(f"{len(track_list)} músicas encontradas. Iniciando download via YouTube...")
    
    for title, artists in track_list:
        query = f"{title} {artists}"
        print(f"Baixando: {query}")
        download_track_youtube(query, output_directory=output_dir)
    
    print("Download concluído. Confira os arquivos MP3 na pasta 'dwYt'.")
