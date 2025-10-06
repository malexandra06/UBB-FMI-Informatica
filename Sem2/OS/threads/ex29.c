/*Scrieti un program C care citeste un numar n si creeaza un sir s de n numere aleatoare intre 0 si 1000. Dupa ce sirul este creat, procesul principal creeaza n + 1 thread-uri. Fiecare din primele n thread-uri repeta urmatorii pasi pana cand sirul s este sortat ascendent:
- genereaza 2 intregi aleatori intre 0 si n-1, numiti i si j
- daca i < j si s[i] > s[j] interschimba s[i] si s[j]
- daca i > j si s[i] < s[j] interschimba s[i] si s[j]
Thread-ul n+1 asteapta pana cand sirul este sortat, dupa care il afiseaza. Folositi mecanisme de sincronizare corespunzatoare.*/

#include <stdio.h>
#include <pthread.h>
#define MAX_SIZE 1000
#include <time.h>
#include <stdlib.h>
int n;
int sir[MAX_SIZE];
//int sortat=0;
pthread_cond_t c;
pthread_mutex_t mtx;
int gata=0;

int sortat(int sir[MAX_SIZE])
{
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(sir[i]>sir[j])
				return 0;
	return 1;
}

void* afiseaza(void* arg)
{
	pthread_mutex_lock(&mtx);
	
	while(sortat(sir)==0)
		pthread_cond_wait(&c,&mtx);

	for(int i=0;i<n;i++)
		printf("%d ",sir[i]);
	pthread_mutex_unlock(&mtx);
	return NULL;
}


void* sorteaza(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&mtx);
		if(gata==1)
		{
			pthread_mutex_unlock(&mtx);
			break;
		}
		int i,j;
		i=rand()%n;
		j=rand()%n;
		while(j==i)
			j=rand()%n;
		if((sir[i]>sir[j] && i<j) || (sir[i]<sir[j] && i>j))
		{
			int aux=sir[i];
			sir[i]=sir[j];
			sir[j]=aux;
		}
		pthread_mutex_unlock(&mtx);
		if(sortat(sir)==1)
		{
			gata=1;
			pthread_cond_signal(&c);
			break;
		}
	}	
	return NULL;
}

int main(int argc,char* argv[])
{
	printf("Introduceti n=");
	scanf("%d",&n);
	srand(time(NULL));

	pthread_t th[n];
	pthread_t print;
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&c,NULL);
	for(int i=0;i<n;i++)
	{
		int x=rand()%1001;
		sir[i]=x;
	}

	for(int i=0;i<n;i++)
	{
		int* arg=malloc(sizeof(int));
		*arg=i;
		pthread_create(&th[i],NULL,sorteaza,arg);
	}
	pthread_create(&print,NULL,afiseaza,NULL);
	for(int i=0;i<n;i++)
        {
                pthread_join(th[i],NULL);
        }
        pthread_join(print,NULL);
	pthread_mutex_destroy(&mtx);
        pthread_cond_destroy(&c);
	return 0;
}
