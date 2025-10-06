/*Scrieti un program C care primeste ca argumente la linia de comanda 2 numere: N si M. Programul va simula o cursa intre N thread-uri care trebuie sa treaca prin M puncte de control. Prin fiecare punct de control thread-urile trebuie sa treaca pe rand (nu se poate ca 2 thread-uri sa fie simultan in acelasi punct de control). Fiecare thread care intra intr-un punct de control va astepta intre 100 si 200 de milisecunde (usleep(100000) face ca un thread sau proces sa astepte 100 de milisecunde) si va afisa un mesaj care va contine numarul thread-ului si numarul punctului de control, apoi va iesi din punctul de control. Fiecare thread va astepta pana cand toate thread-urile au fost create.*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
pthread_barrier_t b;
pthread_mutex_t mtx[1000];

int m,n;

void* func(void* arg)
{
	pthread_barrier_wait(&b);
	int ind=*(int*)arg;
	free (arg);
	int i;
	for(i=0;i<m;i++)
	{

		pthread_mutex_lock(&mtx[i]);
		printf("Threadul %d a intrat in punctul %d\n",ind,i);
		int nr=rand()%101+100;
		usleep(nr);
		pthread_mutex_unlock(&mtx[i]);
	}
	return NULL;
}

int main(int argc,char* argv[])
{
	srand(time(NULL));
	m=atoi(argv[2]);
	n=atoi(argv[1]);
	pthread_barrier_init(&b,NULL,n);
	for(int i=0;i<m;i++)
		pthread_mutex_init(&mtx[i],NULL);
	pthread_t th[n];
	int i;
	for(i=0;i<n;i++)
	{
		int* arg=malloc(sizeof(int));
		*arg=i;
		pthread_create(&th[i],NULL,func,arg);
	}
	for(i=0;i<n;i++)
        {
                pthread_join(th[i],NULL);
        }
	pthread_barrier_destroy(&b);
	for(int i=0;i<m;i++)
		pthread_mutex_destroy(&mtx[i]);
	return 0;
}
