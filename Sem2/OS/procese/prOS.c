#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 1000
#include <malloc.h>
int main(int argc,char* argv[])
{
	(void)argc;
	int fd[2];
	pipe(fd);
	int pid=fork();
	if(pid==0)
	{
		close(fd[1]);
		int k=0;
		char comenzi[BUFFER_SIZE];
		char *p;
		while(read(fd[0],comenzi,sizeof(char)*BUFFER_SIZE)>0)
		{
			k++;
			p=strtok(comenzi," ");
			printf("Comanda: %s\n",p);
			p=strtok(NULL," ");
			printf("Cuvant: %s\n",p);
			//printf("Comanda: %s\n",p);
			//p=strtok(NULL," ");
			//printf("Cuvant: %s\n",p);
		}
	}
	else
	{
		close(fd[0]);
		FILE* desc=fopen(argv[1],"r");
		char s[100];
		while(fgets(s,sizeof(s),desc))
			if(strcmp(s,"\n")!=0)
			{
				s[strlen(s)]='\0';
				write(fd[1],s,strlen(s));
			}
		fclose(desc);
		close(fd[1]);
		wait(NULL);
	}
	return 0;
}
