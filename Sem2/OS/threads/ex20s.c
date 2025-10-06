/*Scrieti un program C care primeste ca argumente la linia de comanda 2 numere: N si M. Programul va simula o cursa intre N thread-uri care trebuie sa treaca prin M puncte de control. Prin fiecare punct de control thread-urile trebuie sa treaca pe rand (nu se poate ca 2 thread-uri sa fie simultan in acelasi punct de control). Fiecare thread care intra intr-un punct de control va astepta intre 100 si 200 de milisecunde (usleep(100000) face ca un thread sau proces sa astepte 100 de milisecunde) si va afisa un mesaj care va contine numarul thread-ului si numarul punctului de control, apoi va iesi din punctul de control. Fiecare thread va astepta pana cand toate thread-urile au fost create.*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX_TH 1000
#include <time.h>

int m,n;
pthread_mutex_t mtx[MAX_TH];
pthread_barrier_t barr;

void* routine(void* arg)
{
	int ind=*(int*)arg;
        free(arg);
	printf("Thread-ul %d asteapta la bariera\n",ind);
	pthread_barrier_wait(&barr);
	for(int i=0;i<m;i++)
	{
		pthread_mutex_lock(&mtx[i]);
		printf("Thread-ul %d a ajuns in punctul %d\n",ind,i);
		int nr=rand()%100001+100000;
		usleep(nr);
		pthread_mutex_unlock(&mtx[i]);
	}
	printf("Thread-ul %d a finalizat cursa\n",ind);
	return NULL;
}

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("%s","Nu ati introdus suficiente argumente sau ati introdus prea multe");
		exit(1);
	}

	n=atoi(argv[1]);
	m=atoi(argv[2]);
	srand(time(NULL));
	pthread_t th[n];
	pthread_barrier_init(&barr,NULL,n);
	for(int i=0;i<m;i++)
		pthread_mutex_init(&mtx[i],NULL);
	for(int i=0;i<n;i++)
	{
		int* arg=malloc(sizeof(int));
		*arg=i;
		if(pthread_create(&th[i],NULL,routine,arg))
		{
			perror("Create failed");
			exit(2);
		}
	}
	for(int i=0;i<n;i++)
        {
                if(pthread_join(th[i],NULL))
                {
                        perror("Join failed");
                        exit(3);
                }
        }
	pthread_barrier_destroy(&barr);
	for(int i=0;i<m;i++)
                pthread_mutex_destroy(&mtx[i]);
	return 0;
}
