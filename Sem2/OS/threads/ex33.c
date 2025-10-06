/*Scrieti un program C care creeaza N threaduri (N dat ca argument la linia de comanda). Programul principal deschide un fisier F, primit de la linia de comanda (fisierul contine doar cuvinte de maximum 20 de caractere, separate prin spatii). Fiecare thread va executa ture de citit intre 1 si 3 cuvinte din fisier si le va concatena la un buffer local, pana cand tot continutul fisierului a fost parcurs. Dupa ce fisierul a fost citit in intregime, threadurile retureaza bufferul lor local si procesul princial afiseaza resultatul de la fiecare thread. Dupa fiecare tura de citire, fiecare thread asteapta dupa celelalte threaduri inainte sa inceapa o noua tura de citire.*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int n;
FILE* fd;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;
int gata=0;

void* routine(void* arg)
{
    char* sir = malloc(2000);
    sir[0] = '\0';
    char cuv[21];

    while (1)
    {
        pthread_mutex_lock(&mtx);
        if (gata)
        {
            pthread_mutex_unlock(&mtx);
            // toate thread-urile ajung aici la barieră
            pthread_barrier_wait(&barr);
            break;
        }

        int nr = rand() % 3 + 1;
        int i;
        for (i = 0; i < nr; i++)
        {
            if (fscanf(fd, "%20s", cuv) != 1)
            {
                gata = 1;
                break;
            }
            if (strlen(sir) > 0)
                strcat(sir, " ");
            strcat(sir, cuv);
        }
        pthread_mutex_unlock(&mtx);

        pthread_barrier_wait(&barr);
        // verificăm gata după barieră pentru a permite sincronizare
        if (gata) break;
    }

    sir[strlen(sir)]='\0';
        printf("Sirul generat de thread %s\n",sir);
        free(sir);
        return NULL;
}


/*void* routine(void* arg)
{
	char* sir=malloc(2000*sizeof(char));
	char cuv[21];
	sir[0] = '\0';
	while(1)
	{
		pthread_mutex_lock(&mtx);
		if(gata==1)
		{
			pthread_mutex_unlock(&mtx);
			pthread_barrier_wait(&barr);
			break;
		}

		int nr=rand()%3+1;

		for(int i=0;i<nr;i++)
		{
			if(fscanf(fd,"%s",cuv)==-1)
			{
				gata=1;
				pthread_mutex_unlock(&mtx);
				break;
			}
			strcat(sir,cuv);
			strcat(sir," ");
		}

		pthread_mutex_unlock(&mtx);
		usleep(10000);
		pthread_barrier_wait(&barr);
	}	
	sir[strlen(sir)]='\0';
	printf("Sirul generat de thread %s\n",sir);
	free(sir);
	return NULL;
}*/


int main(int argc,char* argv[])
{
	n=atoi(argv[1]);
	fd=fopen(argv[2],"r");
	srand(time(NULL));
	pthread_t th[n];
	pthread_barrier_init(&barr,NULL,n);
	for(int i=0;i<n;i++)
		pthread_create(&th[i],NULL,routine,NULL);

	for(int i=0;i<n;i++)
		pthread_join(th[i],NULL);
	pthread_barrier_destroy(&barr);
	fclose(fd);
	return 0;
}
