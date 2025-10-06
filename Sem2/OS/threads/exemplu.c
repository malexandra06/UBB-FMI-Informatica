#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <malloc.h>

void *generator()
{
	srand(time(NULL));
	int* value=malloc(sizeof(int));
	int n=rand()%10;
	*value=n;
	return (void*)value;
}

int main(int argc,char* argv[])
{
	pthread_t t1;
	int* res;
	pthread_create(&t1,NULL,&generator,NULL);
	pthread_join(t1,(void**)&res);
	printf("Numar %d\n",*res);
	free(res);
	return 0;
}
