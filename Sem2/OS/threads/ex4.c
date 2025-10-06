#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 100
#define NUMBERS_PER_THREAD 1000

long long sume_partiale[NUM_THREADS];

void *f(void *a)
{
    int index = *(int *)a;
    free(a);

    unsigned int seed = time(NULL) + index; // Seed unic per thread
    int nr;
    long long suma = 0;

    for (int i = 0; i < NUMBERS_PER_THREAD; i++) {
        nr = rand_r(&seed); // thread-safe
        suma += nr;
    }

    sume_partiale[index] = suma;
    printf("Suma %d este %lld\n", index, suma);

    return NULL;
}

int main()
{
    pthread_t t[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&t[i], NULL, f, arg);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(t[i], NULL);
    }

    long long suma_totala = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        suma_totala += sume_partiale[i];
    }

    printf("Suma totală este %lld\n", suma_totala);
    return 0;
}

