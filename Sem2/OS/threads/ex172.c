/*Scrieti un program C care citeste de la tastatura un numar N si creeaza 2 thread-uri. Unul dintre thread-uri va genera un numar par si il va insera intr-un thread primit ca parametru. Celalalt thread va genera un numar impar si il va insera in acelasi sir de numere primit ca parametru. Implementati un mecanism de sincronizare intre cele 2 thread-uri astfel incat alterneaza in inserarea de numere in sir, pana cand sirul contine N numere.*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <stdlib.h>
int n;
int len;
int* sir;
pthread_mutex_t mtx;
pthread_cond_t cond;
int ok=0;

void* par(void* arg)
{
	int* sir=(int*)arg;
	while(len<n){
		pthread_mutex_lock(&mtx);
		while(ok==0)
			pthread_cond_wait(&cond,&mtx);
		if(len==n)
		{
			pthread_mutex_unlock(&mtx);
			break;
		}
		int nr=2*(rand()%10);
		printf("[PAR] Introduc numarul %d\n",nr);
		sir[len++]=nr;
		ok=0;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

void* impar(void* arg)
{
        int* sir=(int*)arg;
        while(len<n){
                pthread_mutex_lock(&mtx);
		while(ok==1)
			pthread_cond_wait(&cond,&mtx);
		if(len==n)
                {
                        pthread_mutex_unlock(&mtx);
                        break;
                }
                int nr=2*(rand()%10)+1;
		printf("[IMPAR] Introduc numarul %d\n",nr);
                sir[len++]=nr;
                ok=1;
                pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mtx);
        }
        return NULL;
}

int main()
{
	srand(time(NULL));
	printf("Introduceti n = ");
	scanf("%d",&n);
	sir=malloc(n*sizeof(int));
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_t th[2];
	pthread_create(&th[0],NULL,par,sir);
	pthread_create(&th[1],NULL,impar,sir);

	pthread_join(th[0],NULL);
	pthread_join(th[1],NULL);
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);
	free(sir);
	return 0;
}
