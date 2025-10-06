#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primes[10]={2,3,5,7,11,13,17,19,23,29};
int sumaGlobala=0;
pthread_mutex_t mutex;

void* routine(void* arg)
{
	int*ind=(int*)arg;
	pthread_mutex_lock(&mutex);
	sumaGlobala+=primes[*ind];
	pthread_mutex_unlock(&mutex);
	free(ind);
	return NULL;
}

int main(int argc,char* argv[])
{
	pthread_t th[10];
	int i;
	pthread_mutex_init(&mutex,NULL);
	for(i=0;i<10;i++)
	{
		int*arg=malloc(sizeof(int));
		*arg=i;
		pthread_create(&th[i],NULL,&routine,(void*)arg);	
	}
	for(i=0;i<10;i++)
	{
		pthread_join(th[i],NULL);
	}
	pthread_mutex_destroy(&mutex);
	printf("Suma totala: %d\n",sumaGlobala);
	return 0;
}
