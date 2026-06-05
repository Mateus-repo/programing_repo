Download Spotify Tool – Setup e Instruções de Utilização
========================================================

Este projeto contém scripts Python (por exemplo, download_spotify_v5.py) que:
  • Extraem os metadados (nome e artistas) de uma playlist do Spotify.
  • Procuram e efetuam o download do áudio correspondente do YouTube (convertendo-o para MP3).
  • Geram logs que comparam os títulos do Spotify com os do YouTube, sinalizando avisos (WARN)
    quando os nomes diferem e erros (ERROR) em caso de falhas. Durante a execução, o script
    exibe a contagem atual de ERRORS e WARNS.
  • Cancela imediatamente o processo se a tecla ESC for premida.
  • Valida os ficheiros de configuração: se no url.json o campo "url" tiver o valor "YOUR_PLAYLIST_LINK"
    (ou estiver vazio), o script exibirá um erro e cancelará. Da mesma forma, se em spotify.json os campos
    "client_id" ou "client_secret" estiverem com os valores padrão ("CLIENT_ID", "CLIENT_SECRET") ou vazios,
    o script exibirá um erro pedindo credenciais reais obtidas em https://developer.spotify.com/dashboard.
  • Novo: Se o campo "music_num" estiver ausente, vazio ou incorreto em spotify.json, o valor padrão será  
    considerado como falso e um aviso será exibido durante a execução.

Requisitos
----------
- Python 3 (preferencialmente a versão mais recente)
- Módulos Python: spotipy, yt-dlp
- FFmpeg, que já se encontra na pasta “ffmpeg” do projeto (em “ffmpeg\bin”)
- O projeto utiliza a biblioteca “msvcrt” para detecção de teclas (funciona somente no Windows)

Setup Automatizado
------------------
Um ficheiro de batch chamado **setup.bat** está incluído na raiz do projeto. Ele:
  • Verifica se o Python está instalado; caso não esteja, executa o instalador (python-3.13.5-amd64.exe) presente na raiz.
  • Executa “pip install spotipy yt-dlp” para instalar os módulos necessários.
  • Copia a pasta “ffmpeg” para “C:\ffmpeg” se não for encontrada.
  • Define a variável de ambiente do sistema FFMPEG_DIR apontando para “C:\ffmpeg\bin”.

Para executar o setup:
  1. Certifica-te de que **setup.bat** está na raiz (junto com “spotify.json”, “url.json” e os scripts Python).
  2. Executa o ficheiro **setup.bat** como administrador.
  3. Aguarda a conclusão do processo de setup.

Configuração dos Ficheiros
--------------------------
1. **url.json** – Contém o URL da playlist do Spotify.
   Exemplo:
       {
         "url": "https://open.spotify.com/playlist/2jyu0OrwR3FP3zl5XI8RQa"
       }
   Se o campo "url" estiver com o valor "YOUR_PLAYLIST_LINK" ou estiver vazio, o script exibirá um erro e não prosseguirá.

2. **spotify.json** – Contém as credenciais para acesso à API do Spotify.
   Exemplo:
       {
           "client_id": "hnf6eb6wee6ebyfdryh56",
           "client_secret": "dfgbde535ghddrewsg76e346dfdgw35f",
           "redirect_uri": "https://localhost:8888/callback"
       }
   Se os campos "client_id" ou "client_secret" estiverem com os valores padrões ("CLIENT_ID" ou "CLIENT_SECRET") ou vazios,
   o script exibirá um erro e solicitará as credenciais reais obtidas no Spotify Developer Dashboard.

Estrutura do Projeto
---------------------
A estrutura típica do projeto é:

C:.
│   download_spotify_v#.py
│   setup.bat
│   spotify.json
│   url.json
│   runSpotify_V#.bat  (para executar o script)
├───dwYt              (destino dos ficheiros MP3)
├───ffmpeg            (contém o FFmpeg – "ffmpeg\bin" contém os executáveis)
└───log               (logs gerados durante a execução)

Uso do Script
-------------
Após o setup com **setup.bat**, para executar:
  - Navega até a pasta do projeto (via CMD ou utilizando um ficheiro de lote, por exemplo, runSpotify_VX.bat).
  - Executa o comando:
         python download_spotify_v5.py
Durante a execução:
  • O script exibe o progresso, a média de tempo por faixa, o tempo restante e a contagem corrente de ERRORS e WARNS.
  • Se a tecla ESC for premida, o processamento é cancelado imediatamente.
  • Os ficheiros MP3 são salvos na pasta “dwYt” e os logs são gravados na pasta “log”.

Notas Finais
-----------
- Este projeto foi desenvolvido para Windows (usa “msvcrt” para detecção de teclas).
- Se estiveres a utilizar Linux ou macOS, a funcionalidade ESC precisará ser adaptada.
- Para dúvidas ou suporte, consulta a documentação dos módulos “spotipy” e “yt-dlp” ou contacta o desenvolvedor.

========================================================
