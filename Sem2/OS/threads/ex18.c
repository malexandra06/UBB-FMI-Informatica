/*Scrieti un program C care converteste toate literele mici din argumentele primite la linia de comanda in litere mari
 si afiseaza rezultatul. Folositi un thread pentru fiecare argument.*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
pthread_mutex_t mtx;

void* routine(void* arg)
{
	pthread_mutex_lock(&mtx);
	char* a=(char*)arg;
	for(int i=0;i<strlen(a);i++)
		if(a[i]>='a' && a[i]<='z')
			a[i]=a[i]-32;
	pthread_mutex_unlock(&mtx);
	printf("%s\n",a);
	return NULL;
}

int main(int argc,char* argv[])
{
	pthread_t th[100];
	pthread_mutex_init(&mtx,NULL);
	int i;
	for(i=1;i<argc;i++)
	{
		pthread_create(&th[i],NULL,routine,argv[i]);
	}
	for(i=1;i<argc;i++)
        {
                pthread_join(th[i],NULL);
        }
	printf("Sirul de argumente modificat:\n");
	for(i=1;i<argc;i++)
		printf("%s\n",argv[i]);
	pthread_mutex_destroy(&mtx);
	return 0;
}
