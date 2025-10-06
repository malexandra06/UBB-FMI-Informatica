/*Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte de la tastatură un caracter c şi un şir s şi le trimite prin pipe procesului copil, iar procesul copil verifică şi afişează numărul de apariţii ale caracterului c în şirul s.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_SIZE 100
#include <string.h>
int aparitii(char c,char s[MAX_SIZE])
{
	int nr=0;
	for(int i=0;i<(int)strlen(s);i++)
		if(s[i]==c)
			nr++;
	return nr;
}


int main()
{
	int fd[2];
	pipe(fd);
	if(fork()==0)
	{
		close(fd[1]);
		char c,s[MAX_SIZE];
		read(fd[0],&c,sizeof(char));
		read(fd[0],s,MAX_SIZE*sizeof(char));
		int nr=aparitii(c,s);
		printf("[CHILD] Aparitii: %d \n",nr);
		close(fd[0]);
		exit(0);
	}
	else
	{
		close(fd[0]);
		char c,s[MAX_SIZE];
		printf("%s","Introduceti un caracter c=");
		scanf("%c",&c);
		printf("%s","Introduceti un sir s=");
		scanf("%s",s);
		write(fd[1],&c,sizeof(char));
		write(fd[1],s,sizeof(char)*MAX_SIZE);
		close(fd[1]);
		wait(NULL);}
}
