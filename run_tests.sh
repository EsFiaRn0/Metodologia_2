#!/bin/bash

# ================================
# Compilar t1.c
# ================================
echo "Compilando t1.c..."
gcc t1.c -o t1
if [ $? -ne 0 ]; then
    echo "Error: Falló la compilación."
    exit 1
fi
echo "Compilación completada correctamente."
echo

# ================================
# Ejecutar los tests
# ================================
INPUT_FILE="leetcode_longest_subseq_tests1.txt"
OUTPUT_FILE="resultados.txt"

# Borrar archivo de salida si existe
[ -f "$OUTPUT_FILE" ] && rm "$OUTPUT_FILE"

echo "Ejecutando los test cases..."
counter=0

# Leer archivo línea por línea tomando dos campos por línea
while read -r A B; do
    counter=$((counter + 1))

    # Mostrar progreso cada 5 líneas
    if (( counter % 5 == 0 )); then
        echo "Progreso: $counter"
    fi

    # Ejecutar el programa y guardar solo el tiempo
    ./t1 "$A" "$B" -S >> "$OUTPUT_FILE"

done < "$INPUT_FILE"

echo
echo "Todos los test completados."
echo "Resultados guardados en $OUTPUT_FILE."
