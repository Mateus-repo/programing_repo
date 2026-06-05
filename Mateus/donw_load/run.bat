@echo off
REM Uso: run_download.bat [json_file] [template_saida]

SET JSON=%~1
IF "%JSON%"=="" SET JSON=url.json

REM Template de saída é opcional
SET TEMPLATE=%~2

REM Executa o Python com os parâmetros
python "%~dp0download_audio_json.py" %JSON% %TEMPLATE%

pause
