/*Programul apelat primeste ca argumente doua numere naturale si un nume de fisier si scrie in fisier cel mai mare divizor comun al numerelor. Programul apelant citeste un sir de numere naturale si afisieaza cel mai mare divizor comun al lor.*/

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#define CAPACITATE 100

int main(int argc,char* argv[])
{
	(void)argc;
	(void)argv;
	int* v=(int*)malloc(sizeof(int)*CAPACITATE);
	int n;
	printf("%s","Introduceti n=");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("v[%d]=",i);
		scanf("%d",&v[i]);
	}
	int nr=v[0];
	for(int i=1;i<n;i++)
	{
		int pid=fork();
		if(pid==-1)
		{
			perror("Fork esuat!");
			exit(1);
		}
		else if(pid==0)
		{
			char* cmmdc=(char*)malloc(sizeof(char)*10);
			char* el=(char*)malloc(sizeof(char)*10);
			sprintf(cmmdc,"%d",nr);
			sprintf(el,"%d",v[i]);
			execlp("./apelat5","./apelat5",cmmdc,el,"file5.tmp",NULL);
		}
		else
		{
			wait(NULL);
			int fd=open("file5.tmp",O_RDONLY);
			char* buffer=(char*)malloc(sizeof(char)*10);
			read(fd,buffer,sizeof(buffer));
			nr=atoi(buffer);
			close(fd);
			remove("file5.tmp");	
		}	
	}
	free(v);
	printf("Rezultatul este %d \n",nr);
	return 0;
}
