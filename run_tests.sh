#!/bin/bash

echo "[Etapa 1] Compilando"
gcc t1.c -O0 -o prog_O0
gcc t1.c -O1 -o prog_O1
gcc t1.c -O2 -o prog_O2
gcc t1.c -O3 -o prog_O3

echo "[Etapa 2] Ejecutando experimento"

OUTPUT="resultados.csv"
echo "opt,escenario,n,k,test_id,tiempo,energy_cores,energy_ram" > $OUTPUT

OPTS=("O0" "O1" "O2" "O3")

for opt in "${OPTS[@]}"; do
    EXEC="./prog_$opt"
    echo "[Etapa 3] Optimizacion $opt"

    for esc in A B C; do
        echo "  Escenario $esc"

        for n in 100 200 300 400; do

            case $n in
                100) k=20 ;;
                200) k=30 ;;
                300) k=50 ;;
                400) k=60 ;;
            esac

            archivo="tests/$esc/n$n/tests.txt"
            test_id=1

            while IFS= read -r linea; do
                cadena=$(echo "$linea" | cut -d '"' -f2)

                start=$(date +%s.%N)
                $EXEC "$cadena" "$k" -S > /dev/null
                end=$(date +%s.%N)

                tiempo=$(awk -v s="$start" -v e="$end" 'BEGIN{print e-s}')

                perf_output=$(perf stat -e power/energy-cores/,power/energy-ram/ $EXEC "$cadena" "$k" -S 2>&1 > /dev/null)

                energy_cores=$(echo "$perf_output" | grep "energy-cores" | awk '{print $1}')
                energy_ram=$(echo "$perf_output" | grep "energy-ram" | awk '{print $1}')

                echo "$opt,$esc,$n,$k,$test_id,$tiempo,$energy_cores,$energy_ram" >> $OUTPUT

                test_id=$((test_id+1))
            done < "$archivo"

        done
    done
done

echo "[Etapa 4] Terminado"