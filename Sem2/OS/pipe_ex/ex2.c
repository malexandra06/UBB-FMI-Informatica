/*Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte de la tastatură un număr natural şi îl trimite prin pipe procesului copil, iar procesul copil verifică şi afişează dacă acest număr este prim.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int prim(int x)
{
	if(x<2)
		return 0;
	else if(x==2)
		return 1;
	else
	{
		for(int i=2;i<=x/2;i++)
			if(x%i==0)
				return 0;
		return 1;
	}
}

int main()
{
	int fd[2];
	pipe(fd);
	if(fork()==0)
	{
		close(fd[1]);
		int n;
		read(fd[0],&n,sizeof(int));
		if(prim(n)==1)
			printf("[CHILD]Numarul %d este prim!\n",n);
		else
			printf("[CHILD]Numarul %d nu este prim!\n",n);
		close(fd[0]);
		exit(0);
	}
	else
	{
		close(fd[0]);
		int n;
		printf("%s","[PARENT]Introduceti n=");
		scanf("%d",&n);
		write(fd[1],&n,sizeof(int));
		close(fd[1]);
		wait(NULL);
		exit(0);
	}

}
