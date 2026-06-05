import os
import json
import re
import time
import datetime
import concurrent.futures
import spotipy
from yt_dlp import YoutubeDL
from spotipy.oauth2 import SpotifyClientCredentials
import msvcrt  # USADO APENAS NO WINDOWS para detectar teclas

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

def print_progress(total, completed, avg_time, est_remaining, last_log):
    """
    Atualiza o ecrã com um resumo do progresso.
    O clear screen é chamado apenas periodicamente para não impactar muito na performance.
    """
    os.system("cls")  # Para Windows; para Linux/Mac usar "clear"
    print("=" * 60)
    print(f"Progresso: {completed}/{total} faixas concluídas")
    print(f"Média: {avg_time:.2f} s por faixa")
    print(f"Tempo estimado restante: {est_remaining/60:.2f} minutos")
    print("-" * 60)
    print("Última tarefa processada:")
    print(last_log)
    print("=" * 60)

# -------------------------------------------------
# Integração com Spotify e YouTube
# -------------------------------------------------
def get_spotify_playlist_tracks(playlist_url):
    """Extrai o ID da playlist a partir do URL e retorna uma lista de tuplas (título, artistas)."""
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
        # Se o FFmpeg não estiver no PATH, descomente e ajuste:
        # 'ffmpeg_location': r'C:\ffmpeg\bin',
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
    Se o ficheiro já existir, extrai o título do YouTube; se não, faz o download.
    Retorna uma tupla: (spotify_title, yt_title, elapsed, erro, já_existe)
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
# Fluxo Principal com detecção de ESC para cancelar
# -------------------------------------------------
if __name__ == "__main__":
    # Configuração do Spotify
    spotify_data = load_json("spotify.json")
    client_id = spotify_data.get("client_id")
    client_secret = spotify_data.get("client_secret")
    redirect_uri = spotify_data.get("redirect_uri")
    if not client_id or not client_secret or not redirect_uri:
        print("Verifica que 'spotify.json' contém 'client_id', 'client_secret' e 'redirect_uri'.")
        exit(1)
    os.environ["SPOTIPY_CLIENT_ID"] = client_id
    os.environ["SPOTIPY_CLIENT_SECRET"] = client_secret
    os.environ["SPOTIPY_REDIRECT_URI"] = redirect_uri

    # Carrega a playlist
    url_data = load_json("url.json")
    playlist_url = url_data.get("url")
    if not playlist_url:
        print("O ficheiro 'url.json' deve conter a chave 'url' com o link da playlist do Spotify.")
        exit(1)
    
    output_dir = create_output_directory("dwYt")
    log_dir = create_log_directory("log")
    log_file_name = datetime.datetime.now().strftime("log_%Y%m%d_%H%M%S.log")
    log_file_path = os.path.join(log_dir, log_file_name)
    
    print(f"Obtendo músicas da playlist: {playlist_url}")
    try:
        track_list = get_spotify_playlist_tracks(playlist_url)
    except Exception as e:
        print("Erro ao obter músicas da playlist:", e)
        exit(1)
    
    total_tracks = len(track_list)
    print(f"{total_tracks} músicas encontradas. Iniciando processamento (do final para o início)...")
    
    # Processa o vetor invertido
    reversed_tracks = list(reversed(track_list))
    tasks = [(spotify_title, f"{spotify_title} {artists}") for (spotify_title, artists) in reversed_tracks]
    total_tasks = len(tasks)
    
    completed = 0
    global_start_time = time.time()
    update_interval = 5  # Atualiza o display a cada 5 tarefas
    log_lines = []       # Acumula logs para escrita ao fim

    cancel_requested = False

    max_workers = 8  # Número de workers concorrentes
    with concurrent.futures.ThreadPoolExecutor(max_workers=max_workers) as executor:
        futures = {executor.submit(process_track, spotify_title, query, output_dir): (spotify_title, query)
                   for (spotify_title, query) in tasks}
        
        for future in concurrent.futures.as_completed(futures):
            # Verifica se alguma tecla foi premida para ver se se pretende cancelar
            if msvcrt.kbhit():
                key = msvcrt.getch()
                if key == b'\x1b':  # ESC
                    print("\nProcesso pausado. Queres mesmo cancelar o processo? (Y/N) ou (S/N):", end=" ")
                    answer = input().strip().lower()
                    if answer in ['y', 's']:
                        print("Processo cancelado. A tentar cancelar os downloads pendentes...")
                        cancel_requested = True
                        # Tenta cancelar as tarefas que ainda não foram iniciadas
                        for fut in futures:
                            fut.cancel()
                        break
                    else:
                        print("Continuando o processo...")

            try:
                sp_title, yt_title, elapsed, err, already = future.result()
            except Exception as exc:
                sp_title, query = futures[future]
                log_line = f"ERROR - SPOTIFY - \"{sp_title}\" YOUTUBE - \"DOWNLOAD FAILED: {exc}\""
                log_lines.append(log_line)
                completed += 1
                continue

            completed += 1
            # Calcula a média com base no tempo total de parede desde o início
            current_elapsed = time.time() - global_start_time
            avg_time = current_elapsed / completed
            remaining = total_tasks - completed
            est_remaining = avg_time * remaining

            if err:
                log_line = f"ERROR - SPOTIFY - \"{sp_title}\" YOUTUBE - \"DOWNLOAD FAILED: {err}\""
            else:
                if yt_title is None:
                    yt_title = "N/A"
                if sp_title.strip().lower() == yt_title.strip().lower():
                    log_line = f"SPOTIFY - \"{sp_title}\" YOUTUBE - \"{yt_title}\""
                else:
                    log_line = f"WARN  - SPOTIFY - \"{sp_title}\" YOUTUBE - \"{yt_title}\""
            log_lines.append(log_line)
            
            if completed % update_interval == 0 or completed == total_tasks:
                print_progress(total_tasks, completed, avg_time, est_remaining, log_line)
        
        # Se foi pedido cancelamento, mostra quantas tarefas foram concluídas até então.
        if cancel_requested:
            print(f"\nProcesso cancelado pelo utilizador. Tarefas concluídas: {completed}/{total_tasks}")

    # Escreve os logs acumulados de uma só vez
    with open(log_file_path, "w", encoding="utf-8") as log_file:
        log_file.write("\n".join(log_lines))
    
    if not cancel_requested:
        print("\nProcessamento concluído.")
    print(f"Verifica os ficheiros MP3 na pasta 'dwYt' e os logs em '{log_file_path}'.")
