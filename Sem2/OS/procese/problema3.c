/*Programul apelat primeste ca argumente niste numere si returneaza cod 0 daca produsul lor este pozitiv, 1 daca e negativ si 2 daca e nul. Programul apelant citeste un sir de numere si afiseaza daca produsul lor este pozitiv, negativ sau zero.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXIM 100
int main(int argc,char* argv[])
{
	if (argc < 2) {
    	printf("Folosire: %s numar1 numar2 ...\n", argv[0]);
    	exit(1);
	}
	int pid=fork();
	if(pid==-1)
	{
		perror("fork imposibil!");
		exit(1);
	}
	else if(pid==0)
	{
		execvp("./procedura3",argv);
	}
	int status;
	wait(&status);
	switch(WEXITSTATUS(status))
	{
		case 0: printf("%s","Produsul este pozitiv!\n"); break;
		case 1: printf("%s","Produsul este negativ!\n"); break;
		case 2: printf("%s","Produsul este nul!\n"); break;
	}
	return 0;
}
