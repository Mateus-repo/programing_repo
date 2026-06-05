@echo off
:: Verifica se o script está a ser executado como administrador
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo Este script precisa de ser executado como administrador.
    echo Por favor, clique com o botao direito e escolha "Executar como administrador".
    pause
    exit /b
)

echo.
echo ---------- Verificando a instalacao do Python ----------
where python >nul 2>&1
if %errorlevel% neq 0 (
    echo Python nao esta instalado.
    if not exist "python-3.13.5-amd64.exe" (
        echo O instalador python-3.13.5-amd64.exe nao foi encontrado no diretorio atual.
        pause
        exit /b
    )
    echo Iniciando a instalacao do Python...
    :: Instala de forma silenciosa; os parametros podem variar conforme o instalador
    start /wait python-3.13.5-amd64.exe /quiet InstallAllUsers=1 PrependPath=1
    where python >nul 2>&1
    if %errorlevel% neq 0 (
        echo Falha ao instalar o Python.
        pause
        exit /b
    )
) else (
    echo Python ja esta instalado.
)

echo.
echo ---------- Instalando os modulos Python (spotipy e yt-dlp) ----------
pip install spotipy yt-dlp
if %errorlevel% neq 0 (
    echo Falha ao instalar os modulos Python.
    echo Certifique-se de que o Python esta configurado corretamente e tente novamente.
    pause
    exit /b
)

echo.
echo ---------- Verificando a existencia do FFmpeg ----------
if not exist "C:\ffmpeg\bin\ffmpeg.exe" (
    echo FFmpeg nao foi encontrado em C:\ffmpeg.
    if not exist "ffmpeg" (
         echo A pasta "ffmpeg" nao foi encontrada no diretorio atual.
         pause
         exit /b
    )
    echo Copiando a pasta "ffmpeg" para C:\...
    xcopy /E /I /Y "ffmpeg" "C:\ffmpeg"
    if %errorlevel% neq 0 (
         echo Falha ao copiar a pasta "ffmpeg" para C:\.
         echo Certifique-se de ter permissoes de administrador.
         pause
         exit /b
    ) else (
         echo FFmpeg copiado com sucesso para C:\ffmpeg.
    )
) else (
    echo FFmpeg ja esta presente em C:\ffmpeg.
)

echo.
echo ---------- Definindo a variavel de ambiente FFMPEG_DIR ----------
:: Define a variavel de ambiente do sistema para FFmpeg; /M indica variavel de sistema
setx FFMPEG_DIR "C:\ffmpeg\bin" /M
if %errorlevel% neq 0 (
    echo Falha ao definir a variavel de ambiente FFMPEG_DIR.
    echo Tente executar este script como administrador.
    pause
    exit /b
)

echo.
echo Setup concluido com sucesso!
pause
