#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#define MAX_SIZE 100

int main(int argc,char* argv[])
{
	if(argc<2)
	{
		printf("Argumente insuficiente!\n");
		printf("Utilizare: ./ex4 file1.txt\n");
		return 1;
	}
	int fd[2];
	if(pipe(fd)==-1)
	{
		perror("Pipe esuat...");
		exit(1);
	}
	int pid=fork();
	if(pid==-1)
	{
		perror("Fork esuat...");
		exit(1);
	}
	else if(pid==0)
	{
		close(fd[1]);
		char s[MAX_SIZE];
		read(fd[0],s,sizeof(char)*MAX_SIZE);
		close(fd[0]);
		char*p;
		p=strtok(s," ");
		int cuv,lit;
		cuv=lit=0;
		while(p!=NULL)
		{
			cuv++;
			lit=lit+strlen(p);
			p=strtok(NULL," ");
		}
		printf("Numar litere %d ,cuvinte %d\n",lit,cuv);
		exit(0);
	}
	else
	{
		close(fd[0]);
		int f=open(argv[1],O_RDONLY);
		char s[MAX_SIZE];
		read(f,s,MAX_SIZE*sizeof(char));
		close(f);
		write(fd[1],s,sizeof(char)*MAX_SIZE);
		close(fd[1]);
		wait(NULL);
	}
	return 0;
}
