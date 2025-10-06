#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primes[10]={2,3,5,7,11,13,17,19,23,29};

void* routine(void* arg)
{
	//int number=*(int*)(arg);
	//printf("%d ",number);
	int ind=*(int*)(arg);
	//printf("%d ",primes[ind]);
	int s=0;
	for(int i=ind;i<ind+5;i++)
		s+=primes[i];
	*(int*)arg=s;
	printf("%d\n",s);
	return arg;
}


int main(int argc,char* argv[])
{
	pthread_t th[2];
	int i;
	for(i=0;i<2;i++)
	{
		int*arg=malloc(sizeof(int));
		*arg=i*5;
		pthread_create(&th[i],NULL,&routine,arg);
	}
	int suma=0;
	for(i=0;i<2;i++)
        {
		int* r;
                pthread_join(th[i],(void**)&r);
		suma+=*r;
		free(r);
        }	
	printf("final %d\n",suma);
	return 0;
}
