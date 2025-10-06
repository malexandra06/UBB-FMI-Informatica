/*Scrieti un program C care creeaza 2^N thread-uri care concureaza pana la linia de final (N este argument la linia de comanda). Thread-urile trebuie sa treaca prin N puncte de control. Punctul de control cu numarul X va permite sa treaca simultan prin el un numar de thread-uri egal cu jumatate din numarul de thread-uri permise de punctul de control X - 1 (N >= X >=1). Punctul de control cu numarul 0 (primul) va permite unui numar de 2^(N-1) thread-uri sa treaca simultan.*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX_THREADS 100000
#define MAX_BARR 10000
#include <stdlib.h>
int n;
sem_t sem[MAX_BARR];

int putere(int n)
{
	int x=1;
	while(n>0)
	{
		x=x*2;
		n--;
	}
	return x;
}

void *routine(void* arg)
{
	int ind=*(int*)arg;
	free(arg);
	for(int i=0;i<n;i++)
	{

		sem_wait(&sem[i]);
		printf("Thread-ul %d a trecut de punctul %d\n",ind,i);
		sem_post(&sem[i]);
	
	}
	printf("Thread-ul %d a finalizat cursa\n",ind);
	return NULL;
	
}


int main(int argc,char* argv[])
{
	if(argc<2)
	{
		printf("%s","Nu ati introdus suficiente argumente\n");
		exit(1);
	}
	n=atoi(argv[1]);

	int nr_th=putere(n);
	int nr=nr_th;
	pthread_t th[nr_th];
	nr_th/=2;
	for(int i=0;i<n;i++)
	{
		sem_init(&sem[i],0,nr_th);
		nr_th/=2;
	}

	for(int i=0;i<nr;i++)
	{
		int* arg=malloc(sizeof(int));
		*arg=i;

		if(pthread_create(&th[i],NULL,routine,arg))
		{
			perror("Pthread create failed");
			exit(2);
		}
	}

	for(int i=0;i<nr;i++)
        {
                if(pthread_join(th[i],NULL))
                {
                        perror("Pthread join failed");
                        exit(3);
                }
        }

	for(int i=0;i<n;i++)
        {
                sem_destroy(&sem[i]);
        }
	return 0;
}
