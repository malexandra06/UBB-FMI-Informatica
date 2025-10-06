/*Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte de la tastatură un număr natural şi îl trimite prin pipe procesului copil, iar procesul copil verifică şi afişează dacă acest număr este par sau impar.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
	(void)argc;
	(void)argv;
	int fd[2];
	int ok=pipe(fd);
	if(ok==-1)
	{
		perror("eroare la pipe...");
		exit(1);
	}
	if(fork()==0)
	{
		close(fd[1]);
		int n;
		read(fd[0],&n,sizeof(int));
		if(n%2==0)
			printf("Numarul %d este par\n",n);
		else
			printf("Numarul %d este impar\n",n);
		close(fd[0]);
		exit(0);
	}
	else
	{
		int n;
		close(fd[0]);
		printf("%s","Introduceti n=");
		scanf("%d",&n);
		sleep(2);
		write(fd[1],&n,sizeof(int));
		close(fd[1]);
		wait(NULL);
		exit(0);
	}
}
