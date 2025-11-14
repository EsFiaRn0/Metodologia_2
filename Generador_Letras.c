#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int NUM_TESTS = 1000;
    int MIN_LEN = 89;
    int MAX_LEN = 150;

    FILE *f = fopen("test_1000.txt", "w");
    if (!f) return 1;

    for (int t = 0; t < NUM_TESTS; t++) {
        int len = MIN_LEN + rand() % (MAX_LEN - MIN_LEN + 1);

        char *s = malloc(len + 1);
        if (!s) return 1;

        for (int i = 0; i < len; i++)
            s[i] = 'a' + (rand() % 26);

        s[len] = '\0';

        int k = 2 + rand() % 9;

        fprintf(f, "\"%s\" %d\n", s, k);

        free(s);
    }

    fclose(f);
    return 0;
}
