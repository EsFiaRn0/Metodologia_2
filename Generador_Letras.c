#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#define NUM_TESTS 20

void crear_carpeta(const char *path) {
#ifdef _WIN32
    _mkdir(path);
#else
    mkdir(path, 0777);
#endif
}

int rand_range(int a, int b) {
    return a + rand() % (b - a + 1);
}

// -------------------------------
// Escenario A: repetitivo pero aleatorio
// -------------------------------
void generar_escenario_A(char *dest, int n) {
    int base_len = rand_range(3, 8);
    char base[20];

    for (int i = 0; i < base_len; i++)
        base[i] = 'a' + rand_range(0, 4);

    for (int i = 0; i < n; i++)
        dest[i] = base[i % base_len];

    dest[n] = '\0';
}

// -------------------------------
// Escenario B: aleatorio uniforme
// -------------------------------
void generar_escenario_B(char *dest, int n) {
    for (int i = 0; i < n; i++)
        dest[i] = 'a' + rand_range(0, 25);
    dest[n] = '\0';
}

// -------------------------------
// Escenario C: frecuencias cercanas a k
// -------------------------------
void generar_escenario_C(char *dest, int n, int k) {
    int freq[5];

    freq[0] = k + 1;
    freq[1] = k + 1;
    freq[2] = k;
    freq[3] = k - 1;
    freq[4] = k - 1;

    int sum = freq[0] + freq[1] + freq[2] + freq[3] + freq[4];

    while (sum < n) {
        freq[rand_range(0, 4)]++;
        sum++;
    }

    int idx = 0;
    for (int c = 0; c < 5; c++)
        for (int j = 0; j < freq[c]; j++)
            dest[idx++] = 'a' + c;

    for (int i = n - 1; i > 0; i--) {
        int j = rand_range(0, i);
        char tmp = dest[i];
        dest[i] = dest[j];
        dest[j] = tmp;
    }

    dest[n] = '\0';
}

void guardar_tests_agrupados(const char *ruta, char tests[][2000], int k) {
    FILE *f = fopen(ruta, "w");
    if (!f) {
        printf("Error creando archivo: %s\n", ruta);
        return;
    }

    for (int i = 0; i < NUM_TESTS; i++)
        fprintf(f, "\"%s\" %d\n", tests[i], k);

    fclose(f);
}

// -----------------------------------------------------
int main() {
    srand(time(NULL));

    int tamaños[4] = {100, 200, 300, 400};
    int ks[4]      = {20, 30, 50, 60};
    const char *escenarios[3] = {"A", "B", "C"};

    char tests[NUM_TESTS][2000];
    char ruta[256];
    char carpeta[256];

    crear_carpeta("tests");

    for (int e = 0; e < 3; e++) {

        sprintf(carpeta, "tests/%s", escenarios[e]);
        crear_carpeta(carpeta);

        for (int t = 0; t < 4; t++) {
            int n = tamaños[t];
            int k = ks[t];

            sprintf(carpeta, "tests/%s/n%d", escenarios[e], n);
            crear_carpeta(carpeta);

            for (int i = 0; i < NUM_TESTS; i++) {

                if (e == 0)
                    generar_escenario_A(tests[i], n);
                else if (e == 1)
                    generar_escenario_B(tests[i], n);
                else
                    generar_escenario_C(tests[i], n, k);
            }

            sprintf(ruta, "tests/%s/n%d/tests.txt", escenarios[e], n);
            guardar_tests_agrupados(ruta, tests, k);
        }
    }

    printf("Se generaron los 12 archivos correctamente (cada uno con 20 tests).\n");
    return 0;
}