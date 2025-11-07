
@echo off
setlocal EnableDelayedExpansion

rem --- Configurações iniciais ---
set ARCH=x64
set LOG_DIR=logs
set LOG_FILE=%LOG_DIR%\logBuild.txt
set DATA_REF=2025-06-12
set BASE_PROD=gs1-product
set BASE_PALLET=gs1-pallet
set CONFIG_FILE=config_dpmm.h
set LINK_LIBS=-lole32 -luuid -lshell32

if not exist "%LOG_DIR%" mkdir "%LOG_DIR%"
echo Início da compilação de todos os módulos...>"%LOG_FILE%" 2>&1

rem --- Calcula dias desde DATA_REF para determinar versão major ---
for /f %%I in ('powershell -NoProfile -Command "(New-TimeSpan -Start '%DATA_REF%' -End (Get-Date)).Days"') do set DIAS=%%I
if %DIAS% LSS 0 set DIAS=0
set /a VER_MAJOR=1 + DIAS

call :CompilarDPmm 6
call :CompilarDPmm 8
call :CompilarDPmm 12
call :CompilarDPmm 24

echo.>>"%LOG_FILE%"
echo Compilação concluída. Ver log em "%LOG_FILE%"
pause
exit /b


:CompilarDPmm
  rem --- Parâmetro: DPMM (6, 8, 12 ou 24) ---
  set DPMM=%1
  set DPMM_FOLDER=DPMM%1
  if not exist "%DPMM_FOLDER%" mkdir "%DPMM_FOLDER%"

  rem --- Gera o header de configuração ---
  echo #define DPMM %DPMM%  // 6=152dpi 8=203dpi 12=300dpi 24=600dpi> "%CONFIG_FILE%"

  rem --- Descobre a próxima versão minor livre ---
  set /a VER_MINOR=1
  :ProcurarVersao
    set "NOME_PROD=%BASE_PROD%-%ARCH%-v!VER_MAJOR!-!VER_MINOR!-DPMM-%DPMM%.exe"
    if exist "%DPMM_FOLDER%\!NOME_PROD!" (
      set /a VER_MINOR+=1
      goto ProcurarVersao
    )
    set "NOME_PALLET=%BASE_PALLET%-%ARCH%-v!VER_MAJOR!-!VER_MINOR!-DPMM-%DPMM%.exe"

  echo. >> "%LOG_FILE%"
  echo ==== DPMM %DPMM% — versão v!VER_MAJOR!-!VER_MINOR! ==== >> "%LOG_FILE%"

  rem --- Gera sempre product.res em 64-bits ---
  echo Gerando product.res (pe-x86-64)... >>"%LOG_FILE%"
  windres -F pe-x86-64 product.rc -O coff -o product.res >>"%LOG_FILE%" 2>&1
  if errorlevel 1 (
    echo ERRO ao gerar product.res — ver "%LOG_FILE%" >> "%LOG_FILE%"
    exit /b
  )

  rem --- Compila o executável product (x64) ---
  echo Compilar !NOME_PROD!... >>"%LOG_FILE%"
  g++ -m64 gs1_Win_Products.cpp product.res -mwindows %LINK_LIBS% -o "%DPMM_FOLDER%\!NOME_PROD!" >>"%LOG_FILE%" 2>&1
  if errorlevel 1 (
    echo ERRO ao compilar !NOME_PROD! — ver "%LOG_FILE%" >> "%LOG_FILE%"
    exit /b
  )
  echo Produto gerado: %DPMM_FOLDER%\!NOME_PROD! >> "%LOG_FILE%"

  rem --- Gera sempre pallet.res em 64-bits ---
  echo Gerando pallet.res (pe-x86-64)... >>"%LOG_FILE%"
  windres -F pe-x86-64 pallet.rc -O coff -o pallet.res >>"%LOG_FILE%" 2>&1
  if errorlevel 1 (
    echo ERRO ao gerar pallet.res — ver "%LOG_FILE%" >> "%LOG_FILE%"
    exit /b
  )

  rem --- Compila o executável pallet (x64) ---
  echo Compilar !NOME_PALLET!... >>"%LOG_FILE%"
  g++ -m64 gs1_Win_Pallet.cpp pallet.res -mwindows %LINK_LIBS% -o "%DPMM_FOLDER%\!NOME_PALLET!" >>"%LOG_FILE%" 2>&1
  if errorlevel 1 (
    echo ERRO ao compilar !NOME_PALLET! — ver "%LOG_FILE%" >> "%LOG_FILE%"
    exit /b
  )
  echo Palete gerada: %DPMM_FOLDER%\!NOME_PALLET! >> "%LOG_FILE%"

exit /b