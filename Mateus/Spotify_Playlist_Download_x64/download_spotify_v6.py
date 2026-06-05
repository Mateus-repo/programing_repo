import os
import json
import re
import time
import datetime
import concurrent.futures
import spotipy
from yt_dlp import YoutubeDL
from spotipy.oauth2 import SpotifyClientCredentials
import msvcrt  # USADO NO WINDOWS para detectar teclas

# -------------------------------------------------
# Funções Utilitárias
# -------------------------------------------------
def load_json(file_path):
    if not os.path.isfile(file_path):
        print(f"Ficheiro {file_path} não encontrado.")
        exit(1)
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            return json.load(f)
    except Exception as e:
        print(f"Erro ao carregar {file_path}: {e}")
        exit(1)

def create_output_directory(directory="dwYt"):
    if not os.path.exists(directory):
        os.makedirs(directory)
    return directory

def create_log_directory(directory="log"):
    if not os.path.exists(directory):
        os.makedirs(directory)
    return directory

def sanitize_filename(text):
    return "".join(c for c in text if c.isalnum() or c in " -_").rstrip()

def print_progress(total, completed, avg_time, est_remaining, last_log, error_count, warn_count):
    """
    Atualiza o ecrã com o resumo do progresso.
    O clear screen é chamado apenas periodicamente para economizar em performance.
    """
    os.system("cls")  # No Linux/Mac, use "clear"
    print("=" * 60)
    print(f"Progresso: {completed}/{total} faixas concluídas")
    print(f"Média: {avg_time:.2f} s por faixa")
    print(f"Tempo estimado restante: {est_remaining/60:.2f} minutos")
    print("-" * 60)
    print("Última tarefa processada:")
    print(last_log)
    print("-" * 60)
    print(f"ERRORS - {error_count}, WARNS - {warn_count}")
    print("=" * 60)

# -------------------------------------------------
# Integração com Spotify e YouTube
# -------------------------------------------------
def get_spotify_playlist_tracks(playlist_url):
    """Extrai o ID da playlist e retorna uma lista de tuplas (título, artistas)."""
    pattern = r"playlist/([a-zA-Z0-9]+)"
    match = re.search(pattern, playlist_url)
    if not match:
        raise Exception("Não foi possível extrair o ID da playlist a partir do URL fornecido.")
    playlist_id = match.group(1)
    
    sp = spotipy.Spotify(auth_manager=SpotifyClientCredentials())
    tracks = []
    results = sp.playlist_items(playlist_id)
    tracks.extend(results['items'])
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
    Procura no YouTube (usando 'ytsearch1:') e baixa o áudio convertendo para MP3.
    Retorna o título obtido do YouTube ou uma mensagem de erro.
    """
    ydl_opts = {
        'format': 'bestaudio/best',
        'outtmpl': os.path.join(output_directory, sanitize_filename(query) + '.%(ext)s'),
        'postprocessors': [{
            'key': 'FFmpegExtractAudio',
            'preferredcodec': 'mp3',
            'preferredquality': '192',
        }],
        # Se necessário, pode definir:
        # 'ffmpeg_location': os.path.join(os.getcwd(), "ffmpeg", "bin"),
        'ignoreerrors': True,
        'quiet': True,
        'noplaylist': True,
    }
    search_query = f"ytsearch1:{query}"
    with YoutubeDL(ydl_opts) as ydl:
        try:
            info = ydl.extract_info(search_query, download=True)
            if info is None:
                return None, "Nenhuma informação obtida"
            if 'entries' in info and info['entries']:
                video_info = info['entries'][0]
            else:
                video_info = info
            youtube_title = video_info.get("title", query)
            return youtube_title, None
        except Exception as e:
            return None, str(e)

def extract_youtube_title(query):
    """Extrai o título do YouTube sem fazer download (modo simulado)."""
    ydl_opts = {
        'format': 'bestaudio/best',
        'simulate': True,
        'skip_download': True,
        'quiet': True,
        'noplaylist': True,
    }
    search_query = f"ytsearch1:{query}"
    with YoutubeDL(ydl_opts) as ydl:
        try:
            info = ydl.extract_info(search_query, download=False)
            if info is None:
                return None, "Nenhuma informação obtida"
            if 'entries' in info and info['entries']:
                video_info = info['entries'][0]
            else:
                video_info = info
            youtube_title = video_info.get("title", query)
            return youtube_title, None
        except Exception as e:
            return None, str(e)

def process_track(spotify_title, query, output_directory):
    """
    Se o ficheiro já existir, extrai o título do YouTube; caso contrário, realiza o download.
    Retorna: (spotify_title, yt_title, elapsed, erro, já_existe)
    """
    output_file = os.path.join(output_directory, sanitize_filename(query) + ".mp3")
    if os.path.exists(output_file):
        yt_title, err = extract_youtube_title(query)
        return (spotify_title, yt_title, 0.0, err, True)
    else:
        start_time = time.time()
        yt_title, err = download_track_youtube(query, output_directory=output_directory)
        elapsed = time.time() - start_time
        return (spotify_title, yt_title, elapsed, err, False)

# -------------------------------------------------
# Fluxo Principal com Validações e Cancelamento via ESC
# -------------------------------------------------
if __name__ == "__main__":
    # Carrega e valida spotify.json
    spotify_data = load_json("spotify.json")
    client_id = spotify_data.get("client_id", "").strip()
    client_secret = spotify_data.get("client_secret", "").strip()
    redirect_uri = spotify_data.get("redirect_uri", "").strip()
    if (not client_id) or (client_id.upper() == "CLIENT_ID") or \
       (not client_secret) or (client_secret.upper() == "CLIENT_SECRET"):
        print("Erro: Por favor, insira o client_id e client_secret reais obtidos no https://developer.spotify.com/dashboard")
        exit(1)
    if not redirect_uri:
        print("Erro: O campo 'redirect_uri' não pode estar vazio em spotify.json")
        exit(1)
    
    os.environ["SPOTIPY_CLIENT_ID"] = client_id
    os.environ["SPOTIPY_CLIENT_SECRET"] = client_secret
    os.environ["SPOTIPY_REDIRECT_URI"] = redirect_uri

    # Carrega e valida url.json
    url_data = load_json("url.json")
    playlist_url = str(url_data.get("url", "")).strip()
    if (not playlist_url) or (playlist_url.upper() == "YOUR_PLAYLIST_LINK"):
        print("Erro: Por favor, insira o link real da playlist no ficheiro url.json")
        exit(1)
    
    # Tenta recuperar as faixas para verificar se a playlist existe
    try:
        track_list = get_spotify_playlist_tracks(playlist_url)
    except Exception as e:
        print("Erro ao obter músicas da playlist:", e)
        exit(1)
    if not track_list:
        print("Erro: A playlist não existe ou está vazia.")
        exit(1)
    
    output_dir = create_output_directory("dwYt")
    log_dir = create_log_directory("log")
    log_file_name = datetime.datetime.now().strftime("log_%Y%m%d_%H%M%S.log")
    log_file_path = os.path.join(log_dir, log_file_name)
    
    total_tracks = len(track_list)
    print(f"{total_tracks} músicas encontradas. Iniciando processamento (do final para o início)...")
    
    # Prepara as tarefas (inverte a lista)
    reversed_tracks = list(reversed(track_list))
    tasks = [(spotify_title, f"{spotify_title} {artists}") for (spotify_title, artists) in reversed_tracks]
    total_tasks = len(tasks)
    
    completed = 0
    global_start_time = time.time()  # Tempo total (wall clock)
    update_interval = 5               # Atualiza o display a cada 5 tarefas
    log_lines = []                    # Acumula os logs

    error_count = 0
    warn_count = 0

    cancel_requested = False

    max_workers = 8  # Número de workers concorrentes
    with concurrent.futures.ThreadPoolExecutor(max_workers=max_workers) as executor:
        futures = {executor.submit(process_track, spotify_title, query, output_dir): (spotify_title, query)
                   for (spotify_title, query) in tasks}
        
        for future in concurrent.futures.as_completed(futures):
            # Verifica imediatamente se ESC foi premido; se sim, cancela o processo de imediato
            if msvcrt.kbhit():
                key = msvcrt.getch()
                if key == b'\x1b':  # ESC key
                    print("\nProcesso cancelado pelo utilizador.")
                    cancel_requested = True
                    for fut in futures:
                        fut.cancel()
                    break

            try:
                sp_title, yt_title, elapsed, err, already = future.result()
            except Exception as exc:
                sp_title, query = futures[future]
                log_line = f"ERROR - SPOTIFY - \"{sp_title}\" YOUTUBE - \"DOWNLOAD FAILED: {exc}\""
                log_lines.append(log_line)
                error_count += 1
                completed += 1
                continue

            completed += 1
            current_elapsed = time.time() - global_start_time
            avg_time = current_elapsed / completed
            remaining = total_tasks - completed
            est_remaining = avg_time * remaining

            if err:
                log_line = f"ERROR - SPOTIFY - \"{sp_title}\" YOUTUBE - \"DOWNLOAD FAILED: {err}\""
                error_count += 1
            else:
                if yt_title is None:
                    yt_title = "N/A"
                if sp_title.strip().lower() == yt_title.strip().lower():
                    log_line = f"SPOTIFY - \"{sp_title}\" YOUTUBE - \"{yt_title}\""
                else:
                    log_line = f"WARN  - SPOTIFY - \"{sp_title}\" YOUTUBE - \"{yt_title}\""
                    warn_count += 1
            log_lines.append(log_line)
            
            if completed % update_interval == 0 or completed == total_tasks:
                print_progress(total_tasks, completed, avg_time, est_remaining, log_line, error_count, warn_count)
        
        if cancel_requested:
            print(f"\nProcesso cancelado. Tarefas concluídas: {completed}/{total_tasks}")

    with open(log_file_path, "w", encoding="utf-8") as log_file:
        log_file.write("\n".join(log_lines))
    
    if not cancel_requested:
        print("\nProcessamento concluído.")
    print(f"ERRORS - {error_count}, WARNS - {warn_count}")
    print(f"Verifica os ficheiros MP3 na pasta 'dwYt' e os logs em '{log_file_path}'.")
