/*Scrieti un program C care citeste de la tastatura un numar N si creeaza 2 thread-uri. Unul dintre thread-uri va genera un numar par si il va insera
 intr-un thread primit ca parametru. Celalalt thread va genera un numar impar si il va insera in acelasi sir de numere primit ca parametru. Implementati
 un mecanism de sincronizare intre cele 2 thread-uri astfel incat alterneaza in inserarea de numere in sir, pana cand sirul contine N numere.*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
int* sir;
int n,len;
pthread_mutex_t mtx;
pthread_cond_t c;
int inserat=0;
void* par(void* arg)
{
	while(len<n)
	{
		pthread_mutex_lock(&mtx);
		while(inserat!=1 && len<n)
			pthread_cond_wait(&c,&mtx);
                if (len >= n) {
        	pthread_mutex_unlock(&mtx);
        	break;
    		}
		sir[len]=2*(rand()%10);
                printf("Thread par am inserat %d\n",sir[len]);
                len++;
                inserat=0;
		pthread_cond_signal(&c);
		pthread_mutex_unlock(&mtx);
	}		
	return NULL;
}

void* impar(void* arg)
{
	 while(len<n)
        {
                pthread_mutex_lock(&mtx);
		while(inserat!=0 && len<n)
			pthread_cond_wait(&c,&mtx);
		if (len >= n) {
        	pthread_mutex_unlock(&mtx);
        	break;
    		}
                sir[len]=2*(rand()%10)+1;
                printf("Thread impar am inserat %d\n",sir[len]);
                len++;
		inserat=1;
		pthread_cond_signal(&c);
                pthread_mutex_unlock(&mtx);
        }
        return NULL;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	printf("Introduceti n=");
	scanf("%d",&n);
	sir=malloc(n*sizeof(int));
	pthread_t th[2];
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&c,NULL);
	int i;
	srand(time(NULL));
	inserat=rand()%2;
	pthread_create(&th[0],NULL,par,NULL);
	pthread_create(&th[1],NULL,impar,NULL);
	
	
	pthread_join(th[0],NULL);
        pthread_join(th[1],NULL);
	for(i=0;i<n;i++)
		printf("%d ",sir[i]);	
	free(sir);
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&c);
	return 0;
}
