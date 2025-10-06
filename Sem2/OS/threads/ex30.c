/*Scrieti un program C care citeste un numar n de la tastatura si apoi creeaza n thread-uri numerotate de la 0 la n - 1. Fiecare thread pune un numar aleator intre 10 si 20 pe pozitia indicata de indexul sau intr-un sir de intregi. Dupa ce toate thread-urile au adaugat numarul in sir, fiecare thread repeta urmatorii pasi:
- Verifica daca numarul din sir de pe indexul sau este mai mare ca 0.
- Daca da, scade 1 din toate numerele din sir exceptand numarul de pe pozitia sa.
- Daca nu, isi incheie executia.
- Daca nu mai exista numere mai mari ca 0 in sir, exceptand numarul de pe pozitia sa, atunci isi incheie executia.
Dupa ce toate thread-urile isi incheie executia, procesul principal afiseaza sirul de numere. Folositi mecanisme de sincronizare corespunzatoare.*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 5000

int n;
int sir[MAX_SIZE];
pthread_barrier_t barr;
pthread_mutex_t mtx;

int cond3(int poz)
{
	for(int i=0;i<n;i++)
		if(i!= poz && sir[i]>0)
			return 0;
	return 1;
}

void* routine(void* arg)
{
	int ind=*(int*)arg;
	free(arg);
	int nr=rand()%11+10;
	sir[ind]=nr;
	printf("Thread-ul %d a introdus numarul %d\n",ind,nr);
	pthread_barrier_wait(&barr);
	while(1)
	{
		pthread_mutex_lock(&mtx);
		if(sir[ind]<=0)
		{
			printf("Numarul de pe indicele %d este negativ ma opresc\n",ind);
			pthread_mutex_unlock(&mtx);
			break;
		}
		else
		{
			for(int i=0;i<n;i++)
			{	if(i!=ind)
					sir[i]--;
				printf("%d ",sir[i]);
			}
			printf("\n");
			if(cond3(ind))
			{
				printf("TH %d: Ma opresc pentru ca celelalte numere sunt negative\n",ind);
				pthread_mutex_unlock(&mtx);
				break;
			}
		}
		pthread_mutex_unlock(&mtx);
		usleep(2000000);
	}
	return NULL;
}

int main(int argc,char* argv[])
{
	printf("Introduceti n=");
	scanf("%d",&n);
	pthread_t th[n];
	pthread_barrier_init(&barr,NULL,n);
	pthread_mutex_init(&mtx,NULL);
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		int* arg=malloc(sizeof(int));
		*arg=i;
		if(pthread_create(&th[i],NULL,routine,arg))
		{
			perror("PTHREAD_CREATE FAILED");
			exit(1);
		}
	}
	for(int i=0;i<n;i++)
        {
                if(pthread_join(th[i],NULL))
                {
                        perror("PTHREAD_JOIN FAILED");
                        exit(2);
                }
        }
	pthread_barrier_destroy(&barr);
	pthread_mutex_destroy(&mtx);
	printf("Sirul generat\n");
	for(int i=0;i<n;i++)
		printf("%d ",sir[i]);
	printf("\n");
	return 0;
}
