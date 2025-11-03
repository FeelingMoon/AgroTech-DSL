@echo off
REM ============================================
REM Script de Instalacion Automatica
REM DSL Agricultura - Windows Edition
REM ============================================

title Instalacion DSL Agricultura

echo.
echo ================================================
echo   INSTALADOR DSL AGRICULTURA - WINDOWS
echo   Version 2.0
echo ================================================
echo.

REM Verificar permisos de administrador
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo [!] ADVERTENCIA: Se recomienda ejecutar como Administrador
    echo     para evitar problemas con permisos
    echo.
    pause
)

echo [PASO 1/5] Verificando herramientas necesarias...
echo ================================================
echo.

REM Array de herramientas requeridas
set "tools=gcc flex bison qmake"
set "missing="

for %%t in (%tools%) do (
    echo Verificando %%t...
    where %%t >nul 2>&1
    if errorlevel 1 (
        echo    [X] %%t NO encontrado
        set "missing=!missing! %%t"
    ) else (
        echo    [OK] %%t encontrado
    )
)

echo.
if not "%missing%"=="" (
    echo ================================================
    echo   HERRAMIENTAS FALTANTES DETECTADAS
    echo ================================================
    echo.
    echo Las siguientes herramientas no estan instaladas:
    echo %missing%
    echo.
    echo Por favor instala primero:
    echo   1. MSYS2 desde: https://www.msys2.org/
    echo   2. Qt 6.x desde: https://www.qt.io/download
    echo.
    echo Luego ejecuta este instalador nuevamente.
    echo.
    pause
    exit /b 1
)

echo.
echo [OK] Todas las herramientas estan instaladas
echo.
pause

REM ============================================
echo.
echo [PASO 2/5] Verificando estructura de carpetas...
echo ================================================
echo.

if not exist "transpilador\" (
    echo [!] Creando carpeta transpilador...
    mkdir transpilador
)

if not exist "IDE\" (
    echo [!] Creando carpeta IDE...
    mkdir IDE
)

if not exist "docs\" (
    echo [!] Creando carpeta docs...
    mkdir docs
)

echo [OK] Estructura de carpetas verificada
echo.
pause

REM ============================================
echo.
echo [PASO 3/5] Compilando Transpilador...
echo ================================================
echo.

cd transpilador

if not exist "lexer.l" (
    echo [!] ERROR: No se encuentran los archivos fuente del transpilador
    echo     Asegurate de copiar: lexer.l, parser.y, ast.h, codegen.h
    cd ..
    pause
    exit /b 1
)

echo Generando analizador lexico...
flex lexer.l
if errorlevel 1 (
    echo [!] ERROR al generar lexer
    cd ..
    pause
    exit /b 1
)

echo Generando analizador sintactico...
bison -d parser.y
if errorlevel 1 (
    echo [!] ERROR al generar parser
    cd ..
    pause
    exit /b 1
)

echo Compilando transpilador...
g++ -std=c++11 -Wall -o transpilador.exe lex.yy.c parser.tab.c
if errorlevel 1 (
    echo [!] ERROR al compilar transpilador
    cd ..
    pause
    exit /b 1
)

echo.
echo [OK] Transpilador compilado exitosamente
echo      Archivo creado: transpilador\transpilador.exe
echo.

cd ..
pause

REM ============================================
echo.
echo [PASO 4/5] Compilando IDE...
echo ================================================
echo.

cd IDE

if not exist "IDE-Agricultura.pro" (
    echo [!] ERROR: No se encuentran los archivos fuente del IDE
    echo     Asegurate de copiar todos los archivos .cpp, .h y .pro
    cd ..
    pause
    exit /b 1
)

echo Generando Makefile con qmake...
qmake IDE-Agricultura.pro
if errorlevel 1 (
    echo [!] ERROR al ejecutar qmake
    cd ..
    pause
    exit /b 1
)

echo Compilando IDE (esto puede tardar unos minutos)...
mingw32-make >nul 2>&1
if errorlevel 1 (
    REM Intentar con make si mingw32-make falla
    make >nul 2>&1
    if errorlevel 1 (
        echo [!] ERROR al compilar IDE
        cd ..
        pause
        exit /b 1
    )
)

echo.
echo [OK] IDE compilado exitosamente

if exist "bin\IDE-Agricultura.exe" (
    echo      Archivo creado: IDE\bin\IDE-Agricultura.exe
) else if exist "IDE-Agricultura.exe" (
    echo      Archivo creado: IDE\IDE-Agricultura.exe
) else (
    echo [!] ADVERTENCIA: No se encuentra el ejecutable del IDE
)

echo.

cd ..
pause

REM ============================================
echo.
echo [PASO 5/5] Configuracion final...
echo ================================================
echo.

REM Copiar DLLs necesarias si es posible
if exist "IDE\bin\IDE-Agricultura.exe" (
    echo Intentando copiar DLLs de Qt...
    cd IDE\bin
    windeployqt IDE-Agricultura.exe --no-translations >nul 2>&1
    if errorlevel 0 (
        echo [OK] DLLs de Qt copiadas
    ) else (
        echo [!] No se pudieron copiar DLLs automaticamente
        echo     Ejecuta manualmente: windeployqt IDE-Agricultura.exe
    )
    cd ..\..
)

echo.
echo Creando acceso directo...

REM Crear script de inicio
echo @echo off > Iniciar-IDE.bat
echo cd IDE\bin >> Iniciar-IDE.bat
echo start IDE-Agricultura.exe >> Iniciar-IDE.bat
echo exit >> Iniciar-IDE.bat

echo [OK] Script de inicio creado: Iniciar-IDE.bat

echo.
echo ================================================
echo   INSTALACION COMPLETADA EXITOSAMENTE
echo ================================================
echo.
echo Archivos creados:
echo   - transpilador\transpilador.exe
echo   - IDE\bin\IDE-Agricultura.exe
echo   - Iniciar-IDE.bat
echo.
echo Para ejecutar el IDE:
echo   1. Doble click en: Iniciar-IDE.bat
echo   O
echo   2. Navega a IDE\bin\ y ejecuta IDE-Agricultura.exe
echo.
echo Para probar el transpilador directamente:
echo   cd transpilador
echo   transpilador.exe tu_archivo.agro
echo.
echo Documentacion disponible en: docs\
echo Ejemplos disponibles en: ejemplos\
echo.
echo ================================================
echo   Feliz automatizacion agricola!
echo ================================================
echo.

pause
