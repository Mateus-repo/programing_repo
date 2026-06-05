#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import json
import os
import sys
import argparse
import shutil
from pathlib import Path
from yt_dlp import YoutubeDL

STYLE_HEADER = """[Script Info]
Title: Anime-Style Crunchyroll-Like
ScriptType: v4.00+
WrapStyle: 0
ScaledBorderAndShadow: yes

[V4+ Styles]
Format: Name, Fontname, Fontsize, PrimaryColour, SecondaryColour, OutlineColour, BackColour, Bold, Italic, Underline, StrikeOut, ScaleX, ScaleY, Spacing, Angle, BorderStyle, Outline, Shadow, Alignment, MarginL, MarginR, MarginV, Encoding
Style: Default,Arial Rounded MT Bold,38,&H00FFFFFF,&H00000000,&H00000000,&H00000000,0,0,0,0,100,100,0,0,1,6,0,2,10,10,50,1

[Events]
Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text
"""

def carregar_urls(path):
    try:
        with open(path, 'r', encoding='utf-8') as f:
            return json.load(f)
    except Exception as e:
        print(f"Erro ao ler '{path}': {e}")
        sys.exit(1)

def aplicar_estilo_ass(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    if "[V4+ Styles]" not in content:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(STYLE_HEADER + '\n' + content)
        print(f"✔ Estilo aplicado em: {os.path.basename(file_path)}")

def organizar_legendas_por_idioma(output_dir):
    """Move legendas para pastas organizadas por idioma"""
    legendas_dir = Path(output_dir)
    pt_dir = legendas_dir / "pt"
    eng_dir = legendas_dir / "eng"
    
    # Criar pastas se não existirem
    pt_dir.mkdir(exist_ok=True)
    eng_dir.mkdir(exist_ok=True)
    
    # Processar todos os arquivos de legenda
    for arquivo in legendas_dir.glob("*.ass"):
        nome_arquivo = arquivo.name
        
        # Identificar idioma pelo nome do arquivo
        if '.pt-pt.' in nome_arquivo or '.pt.' in nome_arquivo:
            # Prioridade para pt-pt, depois pt-br/pt genérico
            destino = pt_dir / nome_arquivo
            shutil.move(str(arquivo), str(destino))
            print(f"📁 Movido para /pt/: {nome_arquivo}")
            
        elif '.pt-br.' in nome_arquivo:
            # pt-br vai para pasta pt também
            destino = pt_dir / nome_arquivo
            shutil.move(str(arquivo), str(destino))
            print(f"📁 Movido para /pt/: {nome_arquivo}")
            
        elif '.en.' in nome_arquivo or '.eng.' in nome_arquivo:
            # Inglês vai para pasta eng
            destino = eng_dir / nome_arquivo
            shutil.move(str(arquivo), str(destino))
            print(f"📁 Movido para /eng/: {nome_arquivo}")
        
        # Se não conseguir identificar pelo nome, tentar identificar pelo conteúdo ou deixar na raiz
        else:
            print(f"⚠ Idioma não identificado, mantido na raiz: {nome_arquivo}")

def baixar_legendas(playlist_url, output_dir, cookie_file):
    print(f"\n▶ Baixando legendas de:\n  {playlist_url}\n")
    os.makedirs(output_dir, exist_ok=True)

    # Configuração do yt-dlp com prioridade para pt-pt
    ydl_opts = {
        'skip_download': True,
        'writesubtitles': True,
        'subtitleslangs': ['pt-pt', 'pt-br', 'pt', 'en'],  # Prioridade: pt-pt > pt-br > pt > en
        'subtitlesformat': 'ass',
        'outtmpl': os.path.join(output_dir, '%(playlist_index)02d - %(title)s.%(ext)s'),
        'cookiefile': cookie_file,
        'quiet': False,
        'noplaylist': False,
    }

    with YoutubeDL(ydl_opts) as ydl:
        try:
            ydl.download([playlist_url])
        except Exception as e:
            print(f"Erro no download: {e}")
            return

    # Aplica estilo em todas as .ass geradas
    for fname in os.listdir(output_dir):
        if fname.lower().endswith('.ass'):
            aplicar_estilo_ass(os.path.join(output_dir, fname))

    # Organizar legendas por idioma
    organizar_legendas_por_idioma(output_dir)

def main():
    parser = argparse.ArgumentParser(
        description='Baixa legendas ASS de playlists YouTube com estilo e organização por idioma.'
    )
    parser.add_argument(
        '-j','--json',
        default='url.json',
        help='Ficheiro JSON com URLs (default: url.json)'
    )
    parser.add_argument(
        '-o','--output',
        default='legendas',
        help='Diretório de saída (default: ./legendas/)'
    )
    parser.add_argument(
        '-c','--cookies',
        default='cookies.txt',
        help='Ficheiro de cookies (default: cookies.txt)'
    )
    args = parser.parse_args()

    urls = carregar_urls(args.json)
    for url in urls:
        baixar_legendas(url, args.output, args.cookies)

    print("\n✅ Legendas geradas, estilizadas e organizadas por idioma!")
    print("📂 Estrutura:")
    print("   legendas/")
    print("   ├── pt/     (português pt-pt e pt-br)")
    print("   └── eng/    (inglês)")

if __name__ == '__main__':
    main()