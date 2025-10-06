#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primes[10]={2,3,5,7,11,13,17,19,23,29};

void* routine(void* arg)
{
	//int number=*(int*)(arg);
	//printf("%d ",number);
	int ind=*(int*)(arg);
	printf("%d ",primes[ind]);
	free(arg);
	return NULL;
}


int main(int argc,char* argv[])
{
	pthread_t th[10];
	int i;
	for(i=0;i<10;i++)
	{
		int*arg=malloc(sizeof(int));
		*arg=i;
		pthread_create(&th[i],NULL,&routine,arg);
	}
	for(i=0;i<10;i++)
        {
                pthread_join(th[i],NULL);
        }	
	return 0;
}
