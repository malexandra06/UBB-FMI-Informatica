#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define MAX_SIZE 100000

int fd;
int n,k;
int sir[MAX_SIZE];



void* citeste(void* arg)
{
	for(int i=0;i<n;i++)
		read(fd,&sir[i],1);
	return NULL;
}

void* proceseaza(void* arg)
{
	int ind=*(int*)arg;
	free(arg);
	int st=ind*2000;
	int dr=st+2000;
	int ap=0;
	for(int i=st;i<dr;i++)
		if(sir[i]%k==0)
			ap++;
	printf("Sunt thread %d si in intervalul %d-%d exista %d divizibile cu %d\n",ind,st,dr,ap,k);
	return NULL;
}

int main(int argc,char* argv[])
{
	printf("Introduceti k=");
	scanf("%d",&k);
	printf("Introduceti n=");
	scanf("%d",&n);
	fd=open(argv[1],O_RDONLY);
	pthread_t t1;
	pthread_create(&t1,NULL,citeste,NULL);
	pthread_join(t1,NULL);
	close(fd);

	int nr=n/2000;
	pthread_t th[nr];
	for(int i=0;i<nr;i++)
	{
		int* arg=malloc(sizeof(int));
		*arg=i;
		pthread_create(&th[i],NULL,proceseaza,arg);
	}
	for(int i=0;i<nr;i++)
		pthread_join(th[i],NULL);
	return 0;
}
