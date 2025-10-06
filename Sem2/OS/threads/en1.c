/*1. Generați 100.000 de numere aleatoare și calculați suma lor utilizând 100 thread-uri.*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int globalSum=0;
pthread_mutex_t m;

void* routine(void* arg)
{
	int* ind=(int*)arg;
	srand(*ind);
	int s=0;
	int n;
	printf("Thread-ul %d\n",*ind);
	for(int i=0;i<1000;i++)
	{
		n=rand()%6;
		printf("Generat %d\n",n);
		s+=n;	
	}
	printf("Suma partiala de la thread-ul %d este %d\n",*ind,s);
	pthread_mutex_lock(&m);
	globalSum+=s;
	pthread_mutex_unlock(&m);
	free(arg);
	return NULL;
}	

int main(int argc,char* argv[])
{
	pthread_t th[100];
	int i;
	pthread_mutex_init(&m,NULL);
	for(i=0;i<100;i++)
	{
		int* arg=malloc(sizeof(int));
		*arg=i;
		pthread_create(&th[i],NULL,&routine,(void*)arg);
	}
	for(i=0;i<100;i++)
	{
		pthread_join(th[i],NULL);
	}
	pthread_mutex_destroy(&m);
	printf("Suma totala este %d\n",globalSum);
	return 0;
}
