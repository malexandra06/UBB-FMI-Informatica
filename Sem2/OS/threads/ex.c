#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_CUVANT 21
#define MAX_SIR 2048

int n;
FILE* fd;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
int gata = 0;

void* routine(void* arg) {
    char* sir = malloc(MAX_SIR);
    sir[0] = '\0';
    char cuv[MAX_CUVANT];

    while (1) {
        int cuvinte_citite = 0;

        pthread_mutex_lock(&mtx);
        if (!gata) {
            int nr = rand() % 3 + 1;
            for (int i = 0; i < nr; i++) {
                if (fscanf(fd, "%20s", cuv) == 1) {
                    strcat(sir, cuv);
                    strcat(sir, " ");
                    cuvinte_citite++;
                } else {
                    gata = 1; // nu mai e nimic de citit
                    break;
                }
            }
        }
        pthread_mutex_unlock(&mtx);

        pthread_barrier_wait(&barrier); // sincronizare ture

        // Dacă un thread n-a mai citit nimic și gata == 1, poate ieși
        if (gata && cuvinte_citite == 0) break;
    }

    return sir;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <fisier>\n", argv[0]);
        exit(1);
    }

    n = atoi(argv[1]);
    fd = fopen(argv[2], "r");
    if (!fd) {
        perror("Eroare la deschiderea fisierului");
        exit(1);
    }

    srand(time(NULL));
    pthread_t th[n];
    pthread_barrier_init(&barrier, NULL, n);

    for (int i = 0; i < n; i++) {
        if (pthread_create(&th[i], NULL, routine, NULL) != 0) {
            perror("Eroare la pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < n; i++) {
        char* result;
        pthread_join(th[i], (void**)&result);
        printf("Thread %d a citit: %s\n", i, result);
        free(result);
    }

    pthread_barrier_destroy(&barrier);
    fclose(fd);
    return 0;
}

