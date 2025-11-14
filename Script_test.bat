@echo off
setlocal enabledelayedexpansion

REM ================================
REM Compilar t1.c
REM ================================
echo Compilando t1.c...
gcc t1.c -o t1.exe
if %errorlevel% neq 0 (
    echo Error: Fallo la compilacion.
    exit /b
)
echo Compilacion completada correctamente.
echo.

REM ================================
REM Ejecutar los tests
REM ================================
set INPUT_FILE=leetcode_longest_subseq_tests1.txt
set OUTPUT_FILE=resultados.txt

if exist %OUTPUT_FILE% del %OUTPUT_FILE%

echo Ejecutando los test cases...
set /a counter=0

for /f "usebackq tokens=1,2" %%A in ("%INPUT_FILE%") do (
    set /a counter+=1

    REM Mostrar progreso cada 5
    set /a mod=counter%%5
    if !mod! equ 0 (
        echo Progreso: !counter!
    )

    REM Guardar solo el tiempo en el archivo
    t1.exe %%A %%B -S >> %OUTPUT_FILE%
)

echo.
echo Todos los test completados.
echo Resultados guardados en %OUTPUT_FILE%.
pause