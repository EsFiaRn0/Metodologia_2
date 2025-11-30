/*
    ============================================================================
        Autor:          Miguel Angel Olivares Moraless
        Descripción:    Implementación del algoritmo "Longest Subsequence Repeated K Times"
        Fecha:          12/10/2025  
    ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#define MAXN 1005
#define ALPH 26

static char best[MAXN];
static int best_len = 0;

/*
    ---------------------------------------------------------
    Descripción: Verifica si la subsecuencia 't' puede repetirse al menos 'k' veces dentro de 's'.
    Entrada: t (subsecuencia), s (cadena original), k (número de repeticiones).
    Salida: true si puede repetirse, false en caso contrario.
    ---------------------------------------------------------
*/
bool Repeatable(const char *t, const char *s, int k) {
    if (k == 0) return true;
    int n = strlen(s), m = strlen(t);
    if (m == 0) return true;

    int idx = 0;
    for (int rep = 0; rep < k; rep++) {
        for (int j = 0; j < m; j++) {
            while (idx < n && s[idx] != t[j])
                idx++;
            if (idx >= n)
                return false;
            idx++;
        }
    }
    return true;
}

/*
    ---------------------------------------------------------
    Descripción: Realiza búsqueda recursiva (DFS) con poda para construir la mejor subsecuencia.
    Entrada: p (prefijo), used (uso de letras), L (letras válidas), m (máx. usos), lenL, s, k.
    Salida: Actualiza la mejor subsecuencia global encontrada.
    ---------------------------------------------------------
*/
void SearchPrefix(char *p, int *used, char *L, int *m, int lenL, const char *s, int k) {
    if (!Repeatable(p, s, k))
        return;

    int curr_len = strlen(p);

    if (curr_len > best_len || (curr_len == best_len && strcmp(p, best) > 0)) {
        strcpy(best, p);
        best_len = curr_len;
    }

    int maxPossible = curr_len;
    for (int i = 0; i < lenL; i++) {
        int idx = L[i] - 'a';
        maxPossible += (m[idx] - used[idx]);
    }

    if (maxPossible <= best_len)
        return;

    for (int i = 0; i < lenL; i++) {
        int idx = L[i] - 'a';
        if (used[idx] < m[idx]) {
            used[idx]++;
            int l = strlen(p);
            p[l] = L[i];
            p[l + 1] = '\0';
            SearchPrefix(p, used, L, m, lenL, s, k);
            p[l] = '\0';
            used[idx]--;
        }
    }
}
/*
    ---------------------------------------------------------
    Descripción: Encuentra la subsecuencia más larga de 's' que puede repetirse al menos 'k' veces.
    Entrada: s (cadena original), k (repeticiones requeridas).
    Salida: Cadena con la subsecuencia más larga (debe liberarse con free()).
    ---------------------------------------------------------
*/
char* LongestSubsequenceRepeatedK(const char *s, int k) {
    int n = strlen(s);
    int freq[ALPH] = {0};

    for (int i = 0; i < n; i++)
        freq[s[i] - 'a']++;

    char L[ALPH];
    int m[ALPH] = {0};
    int lenL = 0;

    for (int c = 0; c < ALPH; c++) {
        if (freq[c] >= k) {
            L[lenL++] = 'a' + c;
            m[c] = freq[c] / k;
        }
    }

    // Ordenar en orden lexicográfico descendente
    for (int i = 0; i < lenL; i++) {
        for (int j = i + 1; j < lenL; j++) {
            if (L[i] < L[j]) {
                char tmp = L[i];
                L[i] = L[j];
                L[j] = tmp;
            }
        }
    }

    best[0] = '\0';
    best_len = 0;
    int used[ALPH] = {0};
    char prefix[MAXN] = "";

    SearchPrefix(prefix, used, L, m, lenL, s, k);

    char *res = malloc(strlen(best) + 1);
    strcpy(res, best);
    return res;
}
/*
    ---------------------------------------------------------
    Descripción: Main
    Entrada: Argumentos de línea de comandos -> cadena 's' y entero 'k'.
    Salida: Imprime la subsecuencia más larga repetida 'k' veces.
    ---------------------------------------------------------
*/
int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Uso: %s \"cadena\" k [-V|-S]\n", argv[0]);
        printf("  -V : Verboso\n");
        printf("  -S : Silencioso (solo tiempo)\n");
        return 1;
    }

    const char *s = argv[1];
    int k = atoi(argv[2]);
    const char *mode = argv[3];

    if (k <= 0) {
        printf("Error: k debe ser un entero positivo.\n");
        return 1;
    }

    if (!(strcmp(mode, "-V") == 0 || strcmp(mode, "-S") == 0)) {
        printf("Error: modo debe ser -V o -S\n");
        return 1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    char *ans = LongestSubsequenceRepeatedK(s, k);

    gettimeofday(&end, NULL);

    double wall = (end.tv_sec - start.tv_sec) +
                  (end.tv_usec - start.tv_usec) / 1000000.0;

    if (strcmp(mode, "-V") == 0) {
        printf("Cadena: %s ", s);
        printf("k: %d ", k);
        printf("Resultado: %s ", ans);
        printf("Wall time: %.6f s\n", wall);
    } else {
        printf("%.6f\n", wall);
    }

    free(ans);
    return 0;
}