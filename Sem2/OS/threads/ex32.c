/*Scrieti un program C care primeste un numar N ca argument la linia de comanda. Programul creeaza N thread-uri care vor genera numere aleatoare intre 0 si 111111 (inclusiv) pana cand un thread va genera un numar divizibil cu 1001. Thread-urile vor afisa numerele generate, iar ultimul numar afisat trebuie sa fie cel divizibil cu 1001. Niciun thread nu va incepe sa genereze numere pana cand toate celelalte thread-uri au fost create. Nu se vor folosi variabile globale*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int n;
pthread_barrier_t barr;
pthread_mutex_t mtx;
int gata=0;

void* routine(void* arg)
{
	int ind=*(int*)arg;
	free(arg);
	pthread_barrier_wait(&barr);
	while(1)
	{
		pthread_mutex_lock(&mtx);
		if(gata==1)
		{
			pthread_mutex_unlock(&mtx);
			break;
		}
		int nr=rand()%111112;
		printf("Thread-ul %d a generat %d\n",ind,nr);
		if(nr%1001==0)
		{
			gata=1;
			pthread_mutex_unlock(&mtx);
			break;
		}
		pthread_mutex_unlock(&mtx);
		usleep(2000);
	}
	return NULL;
}

int main(int argc,char* argv[])
{
	n=atoi(argv[1]);
	pthread_t th[n];
	
	srand(time(NULL));
	pthread_barrier_init(&barr,NULL,n);
	pthread_mutex_init(&mtx,NULL);
	for(int i=0;i<n;i++)
	{
		int* arg=malloc(sizeof(int));
		*arg=i;
		pthread_create(&th[i],NULL,routine,arg);
	}

	for(int i=0;i<n;i++)
		pthread_join(th[i],NULL);
	pthread_barrier_destroy(&barr);
	pthread_mutex_destroy(&mtx);
	return 0;
}
