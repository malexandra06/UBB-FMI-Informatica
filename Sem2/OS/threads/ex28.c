/*Scrieti un program C care primeste doua numere, N si M, ca argumente la linia de comanda. Programul creeaza N thread-uri "generator" care genereaza litere mici ale alfabetului aleator si le adauga unui sir de caractere cu 128 de pozitii. Programul mai creeaza un thread "printer" care asteapta ca toate pozitiile sirului de caractere sa fie ocupate, moment in care afiseaza sirul si apoi seteaza toate pozitiile sirului la NULL. Cele N thread-uri "generator" vor genera M astfel de string-uri iar thread-ul "printer" va afisa fiecare string imediat ce ajunge la lungimea 128*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int m,n;
char sir[129];
pthread_cond_t c1,c2;
pthread_mutex_t mtx;
pthread_mutex_t mtx2;
int len=0;
int count=0;

void* generator(void* arg)
{
	int ind=*(int*)arg;
	free(arg);
	while(1){
	pthread_mutex_lock(&mtx);
	while(len==128)
		pthread_cond_wait(&c2,&mtx);
	int nr='z'-'a';
	int x=rand()%nr+1;
	sir[len]='a'+x;
	char c='a'+x;
	printf("Thread-ul %d a intrdus caracterul %c pe pozitia %d\n",ind,c,len);
	len+=1;
	pthread_mutex_unlock(&mtx);
	pthread_cond_signal(&c1);
	if(count==m)
		break;
	}
	return NULL;
}


void* printer(void* arg)
{
	pthread_mutex_lock(&mtx);
	while(1){
	while(len<128)
		pthread_cond_wait(&c1,&mtx);
	printf("Sirul este: %s\n",sir);
	for(int i=0;i<128;i++)
		sir[i]='\0';
	len=0;
	count++;
	if(count==m)
		{pthread_mutex_unlock(&mtx);
		 printf("Nu mai trebuie generate siruri\n");
		break;
		}
	pthread_cond_signal(&c2);}
	return NULL;
}

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("Argumente insuficiente!\n");
		exit(1);
	}
	
	n=atoi(argv[1]);
	m=atoi(argv[2]);
	sir[128]='\0';
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&c1,NULL);
	pthread_cond_init(&c2,NULL);
	//pthread_barrier_init(&barr,0,128);
	pthread_t th[n];
	for(int i=0;i<n;i++)
	{
		int* arg=malloc(sizeof(int));
		*arg=i;
		pthread_create(&th[i],NULL,generator,arg);
	}
	pthread_t print;
	pthread_create(&print,NULL,printer,NULL);

	for(int i=0;i<n;i++)
        {
                pthread_join(th[i],NULL);
        }
	pthread_join(print,NULL);
	pthread_mutex_destroy(&mtx);
        pthread_cond_destroy(&c1);
	pthread_cond_destroy(&c2);
        //pthread_barrier_destroy(&barr);
	return 0;
}
