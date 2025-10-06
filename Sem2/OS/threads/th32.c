/*Scrieti un program C care creeaza N threaduri (N dat ca argument la linia de comanda). Programul principal deschide un fisier F, primit de la linia de comanda (fisierul contine doar cuvinte de maximum 20 de caractere, separate prin spatii). Fiecare thread va executa ture de citit intre 1 si 3 cuvinte din fisier si le va concatena la un buffer local, pana cand tot continutul fisierului a fost parcurs. Dupa ce fisierul a fost citit in intregime, threadurile retureaza bufferul lor local si procesul princial afiseaza resultatul de la fiecare thread. Dupa fiecare tura de citire, fiecare thread asteapta dupa celelalte threaduri inainte sa inceapa o noua tura de citire.*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX_SIZE 1000
#include <time.h>
#include <string.h>

int n;
FILE* fd;
pthread_barrier_t barr;
pthread_mutex_t mtx;
int gata=0;
void* routine(void* arg)
{
    int ind = *(int*)arg;
    free(arg);
    char cuv[20];
    char* buff = malloc(MAX_SIZE * sizeof(char));
    buff[0] = '\0';

    while (1) {
        int terminat_local = 0; // flag local pt ieșire

        pthread_mutex_lock(&mtx);
        if (!gata) {
            int nr = rand() % 3 + 1;
            for (int i = 0; i < nr; i++) {
                if (fscanf(fd, "%s", cuv) <= 0) {
                    gata = 1;
                    terminat_local = 1;
                    printf("Sunt thread %d si s-a terminat citirea\n", ind);
                    break;
                } else {
                    strcat(buff, cuv);
                    strcat(buff, " ");
                }
            }
        } else {
            terminat_local = 1;
            printf("Sunt thread %d si nu mai pot citi\n", ind);
        }
        pthread_mutex_unlock(&mtx);

        // toți trebuie să ajungă aici
        pthread_barrier_wait(&barr);

        // verificare finală pentru ieșire
        if (gata) break;
    }

    printf("Sir generat de thread %d: %s\n", ind, buff);
    free(buff);
    return NULL;
}

/*void* routine(void* arg)
{
	int ind=*(int*)arg;
	free(arg);
	char cuv[20];
	char* buff=malloc(MAX_SIZE*sizeof(char));
	buff[0]='\0';
	while(1)
	{
		pthread_mutex_lock(&mtx);
		if(gata==1)
		{
			printf("Sunt thread %d si nu mai pot citi\n",ind);
			pthread_mutex_unlock(&mtx);
			pthread_barrier_wait(&barr);
			break;
		}
		int nr=rand()%3+1;
		for(int i=0;i<nr;i++)
		{
			if(fscanf(fd,"%s",cuv)<=0)
			{
				gata=1;
				printf("Sunt thread %d si s-a terminat citirea\n",ind);
				pthread_mutex_unlock(&mtx);
				pthread_barrier_wait(&barr);
				break;
			}
			else
			{
				strcat(buff,cuv);
				strcat(buff," ");
			}
		}
		pthread_mutex_unlock(&mtx);
		pthread_barrier_wait(&barr);
	}
	printf("Sir generat de thread %d: %s",ind,buff);
	free(buff);
	return NULL;
}*/

int main(int argc,char* argv[])
{
	n=atoi(argv[1]);
	fd=fopen(argv[2],"r");
	srand(time(NULL));	
	
	pthread_mutex_init(&mtx,NULL);
	pthread_barrier_init(&barr,NULL,n);

	pthread_t th[n];
	for(int i=0;i<n;i++){
		int* arg=malloc(sizeof(int));
		*arg=i;
		pthread_create(&th[i],NULL,routine,arg);
	}
	
	for(int i=0;i<n;i++){
		pthread_join(th[i],NULL);
	}
	fclose(fd);
	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&barr);
	return 0;
}
