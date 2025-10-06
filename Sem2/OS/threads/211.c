#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#define MAX_SIZE 1000

char buff[MAX_SIZE];
float media=0;
pthread_mutex_t mtx;
pthread_barrier_t barr;
float min=INT_MAX;

void* routine(void* arg)
{
	int ind=*(int*)arg;
	free(arg);
	char ch='a'+ind;
	//printf("Sunt thread-ul care cauta litera %c\n",ch);
	
	float ap=0;
	for(int i=0;i<strlen(buff);i++)
		if(buff[i]==ch || buff[i]==ch-32)
			ap++;
	int nr='z'-'a'+1;
	pthread_mutex_lock(&mtx);
	printf("Litera %c a aparut de %f ori\n",ch,ap);
	media+=ap/nr;
	pthread_mutex_unlock(&mtx);
	
	pthread_barrier_wait(&barr);
	//printf("Media aparitiilor: %f\n",media);
	float diff=fabs(ap-media);
	pthread_mutex_lock(&mtx);
	if(ap!=0 && diff<min)
	{
		min=diff;
	}
	pthread_mutex_unlock(&mtx);

	pthread_barrier_wait(&barr);
	if(min==diff)
		printf("Litera %c\n",ch);
	return NULL;
}


int main(int argc,char* argv[])
{
	int fd;
	fd=open(argv[1],O_RDONLY);
	read(fd,buff,MAX_SIZE);
	close(fd);
	int nr='z'-'a'+1;
	pthread_mutex_init(&mtx,NULL);
	pthread_barrier_init(&barr,NULL,nr);
	
	pthread_t th[nr];
	for(int i=0;i<nr;i++)
	{
		int* ind=malloc(sizeof(int));
		*ind=i;
		pthread_create(&th[i],NULL,routine,ind);
	}

	for(int i=0;i<nr;i++)
		pthread_join(th[i],NULL);
	
	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&barr);
	return 0;
}
