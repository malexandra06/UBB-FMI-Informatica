/*Scrieti un program C care primeste ca argumente la linia de comanda numere intregi. Programul va calcula un vector de frecventa pentru cifrele zecimale.
 Pentru fiecare argument, programul va crea un thread care numara aparitiile fiecarei cifre si adauga numarul la pozitia corespunzatoare din vectorul de
 frecventa. Folositi sincronizare eficienta.*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int f[10];
pthread_mutex_t mtx;

void* routine(void*arg)
{
	int nr=*(int*)arg;
	free(arg);
	pthread_mutex_lock(&mtx);
	while(nr!=0)
	{
		sleep(1);
		f[nr%10]++;
		sleep(1);
		nr/=10;
	}
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc,char* argv[])
{
	if(argc<2)
	{
		printf("Nu sunt suficiente argumente!\n");
		exit(1);
	}
	pthread_t th[argc];
	pthread_mutex_init(&mtx,NULL);
	int i;
	for(i=1;i<argc;i++)
	{
		int* nr=malloc(sizeof(int));
		*nr=atoi(argv[i]);
		pthread_create(&th[i],NULL,routine,(void*)nr);
	}
	for(i=1;i<argc;i++)
        {
                pthread_join(th[i],NULL);
        }
	pthread_mutex_destroy(&mtx);
	for(i=0;i<=9;i++)
		printf("%d ",f[i]);
	return 0;
}
