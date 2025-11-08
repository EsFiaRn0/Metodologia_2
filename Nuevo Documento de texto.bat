@echo off
REM ================================
REM Script para ejecutar t1.c con los 1000 test del archivo .txt
REM ================================

setlocal enabledelayedexpansion

REM Compilar el archivo C
echo Compilando t1.c...
gcc t1.c -o t1.exe
if %errorlevel% neq 0 (
    echo Error: Fallo la compilacion.
    pause
    exit /b
)
echo Compilacion completada correctamente.
echo.

REM Ejecutar los 1000 test
set INPUT_FILE=leetcode_longest_subseq_tests.txt
set OUTPUT_FILE=resultados.txt

if exist %OUTPUT_FILE% del %OUTPUT_FILE%

echo Ejecutando los test cases...
set /a counter=0

for /f "usebackq tokens=1,2" %%A in (%INPUT_FILE%) do (
    set /a counter+=1
    echo ============================== >> %OUTPUT_FILE%
    echo Test !counter!: %%A %%B >> %OUTPUT_FILE%
    echo ------------------------------ >> %OUTPUT_FILE%
    echo Entrada: %%A %%B
    t1.exe %%A %%B >> %OUTPUT_FILE%
    echo. >> %OUTPUT_FILE%
)

echo.
echo Todos los test completados.
echo Resultados guardados en %OUTPUT_FILE%.
pause
