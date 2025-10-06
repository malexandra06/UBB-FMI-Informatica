#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define MAX_SIZE 70000
#include <math.h>
#include <limits.h>

int* sir;
int n;
float media;
float min=INT_MAX;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

void* routine(void* arg)
{
	int uc=*(int*)arg;
	free(arg);
	float ap=0;
	for(int i=0;i<n;i++)
		if(sir[i]%10==uc)
			ap++;
	pthread_mutex_lock(&mtx);
	media+=ap/10;
	pthread_mutex_unlock(&mtx);
	pthread_barrier_wait(&barr);
	printf("Media %f\n",media);
	float diff=fabs(media-ap);
	pthread_mutex_lock(&mtx);
	if(diff<min)
		min=diff;
	pthread_mutex_unlock(&mtx);
	pthread_barrier_wait(&barr);
	if(min==diff)
		printf("Cifra %d\n",uc);
	return NULL;
}

int main(int argc,char* argv[])
{
	printf("Introduceti n=");
	scanf("%d",&n);
	sir=malloc(sizeof(int)*70000);
	int fd;
	fd=open(argv[1],O_RDONLY);
	for(int i=0;i<n;i++){
		read(fd,&sir[i],1);}
	close(fd);
	pthread_barrier_init(&barr,NULL,10);
	pthread_t th[10];

	int aparitii[10]={0};
	for(int i=0;i<n;i++)
		aparitii[sir[i]%10]++;
	float md=0;
	for(int i=0;i<10;i++)
		md+=aparitii[i];
	md=md/10;
	
	printf("Raspuns asteptat\n");
float mn = INT_MAX;
for (int i = 0; i < 10; i++) {
    float diff = fabs(md - aparitii[i]);
    if (diff < mn)
        mn = diff;
}
for (int i = 0; i < 10; i++) {
    if (fabs(md - aparitii[i]) == mn)
        printf("Cifra %d\n", i);
}

	printf("Raspuns dat:\n");
	for(int i=0;i<10;i++)
	{
		int* arg=malloc(sizeof(int));
		*arg=i;
		pthread_create(&th[i],NULL,routine,arg);
	}

	for(int i=0;i<10;i++)
		pthread_join(th[i],NULL);
	pthread_barrier_destroy(&barr);
	free(sir);
	return 0;
}
