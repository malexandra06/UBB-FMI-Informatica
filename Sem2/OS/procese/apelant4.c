/*Programul apelat primeste ca argumente doua numere naturale si un nume de fisier si scrie in fisier cel mai mic multiplu comun al numerelor. Programul apelant citeste un sir de numere naturale si afisieaza cel mai mic multiplu comun al lor.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define CAPACITATE 100
int main(int argc,char* argv[])
{
	(void)argc;
	(void)argv;
	int v[CAPACITATE];
	int n;
	printf("%s","Introduceti n=");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("v[%d]=",i);
		scanf("%d",&v[i]);
	}
	int cmmmc=v[0];
	for(int i=1;i<n;i++)
	{
		int pid=fork();
		if(pid==0)
		{
			char cm[10],nr[10];
			sprintf(cm,"%d",cmmmc);
			sprintf(nr,"%d",v[i]);
			execlp("./apelat4","./apelat4",cm,nr,"file4.tmp",NULL);
		}
		else
		{	
			wait(NULL);
			FILE* fd=fopen("file4.tmp","r");
			fscanf(fd,"%d",&cmmmc);
			fclose(fd);
			// Ștergem fișierul temporar
           		remove("file4.tmp");
		}
	}
	printf("Rezultatul este %d \n",cmmmc);
	return 0;
}
