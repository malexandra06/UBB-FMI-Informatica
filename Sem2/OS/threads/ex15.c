/*Scrieti un program care primeste la linia de comanda siruri de caractere. Pentru fiecare sir de caractere programul creeaza un thread care calculeaza
 numarul de cifre, litere si caractere speciale (orice nu e litera sau cifra). Programul principal asteapta ca thread-urile sa isi incheie executia si 
afiseaza rezultatele totale (numarul total de cifre, litere si caractere speciale din toate argumentele primite la linia de comanda) si apoi se incheie.
 Folositi sincronizare eficienta. Nu folositi variabile globale.*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	int cifre,litere,speciale;
}rezultat;

pthread_mutex_t m;
rezultat final;
void* routine(void* arg)
{
	char*s=(char*)arg;
	rezultat* r=malloc(sizeof(rezultat));
	r->cifre=r->litere=r->speciale=0;
	for(int i=0;i<strlen(s);i++)
	{
		if((s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z'))
			r->litere++;
		else if(s[i]>='0' && s[i]<='9')
			r->cifre++;
		else
			r->speciale++;
		sleep(1); 
	}
	pthread_mutex_lock(&m);
	final.litere+=r->litere;
	final.cifre+=r->cifre;
	final.speciale+=r->speciale;
	pthread_mutex_unlock(&m);
	free(arg);
	return r;
}

int main(int argc,char* argv[])
{
	if(argc<2)
	{
		printf("Introduceti siruri de caractere\n");
		exit(1);
	}
	int i;
	pthread_t th[argc];
	pthread_mutex_init(&m,NULL);
	for(i=1;i<argc;i++)
	{
		char* sir=malloc((strlen(argv[i])+1)*sizeof(char));
		strcpy(sir,argv[i]);
		pthread_create(&th[i],NULL,routine,(void*)sir);
	}
	for(i=1;i<argc;i++){
		rezultat* r;
		pthread_join(th[i],&r);
		printf("Rezultate %d: %d litere, %d cifre, %d speciale\n",i,r->litere,r->cifre,r->speciale);
		free(r);
	}
	pthread_mutex_destroy(&m);
	printf("Calcul final: litere %d, cifre %d, speciale %d\n",final.litere,final.cifre,final.speciale);
	return 0;
}
