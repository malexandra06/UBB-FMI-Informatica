/*Programul apelat primeste ca argumente un nume de fisier si une sir de caractere si scrie in fisier sirul oglindit. Programul apelat citeste niste siruri de caractere si concateneaza oglindirile lor.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXIM 100
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc,char* argv[])
{
	char fisier[20],string[MAXIM*argc+1],sir[100];
	string[0] = '\0';
	for(int i=1;i<argc;i++)
	{
		sprintf(fisier,"fisier%d",i);
		int pid=fork();
		if(pid==0)
		{
			execlp("./procedura2", "./procedura2", fisier, argv[i], NULL);
		}
		else if(pid==-1)
		{
			printf("Fork esuat\n");
			exit(1);
		}
	}
	for(int i=1;i<argc;i++){
		int status;
		wait(&status);
		switch (WEXITSTATUS(status)) {
            	case 1: printf("Eroare la fisier\n");break;
        }

	}
	for(int i=1;i<argc;i++)
	{
		sprintf(fisier,"fisier%d",i);
                        int fd = open(fisier, O_RDONLY);
                        read(fd,sir,100);
                        close(fd);
                        strcat(string,sir);
                        strcat(string," ");
	}
	string[strlen(string)]='\0';
	printf("%s",string);
	
	return 0;
}
