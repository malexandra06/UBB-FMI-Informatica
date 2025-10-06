/*Scrieti un program C care primeste ca argument la linia de comanda un intreg N, 
apoi citeste de la tastatura N intregi si ii stocheaza intr-un sir. 
Programul calculeaza suma tuturor intregilor cititi folosind thread-uri care respecta ierarhia prezentata in imagine.
Pentru orice N, sirul de intregi trebuie extins cu valori de 0 astfel incat numarul de elemente din sir sa fie
 o putere a lui 2 (fie numarul acesta M). Numarul de thread-uri necesare va fi M - 1, vom aloca cate un ID intre
 1 si M - 1 fiecarui thread. Conform imaginii, thread-urile cu ID >= M / 2 vor calcula suma a doua numere de pe pozitii
 consecutive din sir. Thread-urile cu ID < M / 2 trebuie sa astepte
 dupa alte 2 thread-uri si apoi vor aduna rezultatul produs de cele 2 thread-uri.*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX_NR 1000

int sir[MAX_NR];

int este_putere(int x)
{
	while(x%2==0)
	{
		x=x/2;
	}
	if(x==1)
		return 1;
	return 0;
}

void* sum(void* arg)
{
	int ind=*(int*)arg;
	sir[ind]+=sir[ind+1];
	//printf("%d\n",sir[ind]);
	free(arg);
	return NULL;
}

void* sum_threads(void* arg)
{
	int ind=*(int*)arg;
	
	return NULL;
}

int main(int argc,char* argv[])
{
	int n=atoi(argv[1]);
	for(int i=0;i<n;i++)
		scanf("%d",&sir[i]);
	int old=n;
	while(este_putere(n)==0)
		n++;

	pthread_t th[n];
	int i;
	int nr=0;
	for(i=1;i<n;i++)
	{	
		int* arg=malloc(sizeof(int));
		if(i>=n/2)
			{
			*arg=nr;
			pthread_create(&th[i],NULL,sum,arg);
			nr+=2;
			}
		else
			{	*arg=nr;
				pthread_create(&th[i],NULL,sum_threads,arg);
				nr+=2;
			}
	}
	for(i=1;i<n;i++)
                pthread_join(th[i],NULL);
	for(i=0;i<n/2;i++)
		printf("%d\n",sir[2*i]);	
	return 0;
}
