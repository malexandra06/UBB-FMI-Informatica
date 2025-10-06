/*Scrieti un program C care genereaza N numere intregi aleatoate (N dat la linia de comanda). Apoi creeaza un proces fiu si ii trimite numerele prin pipe. Procesul fiu calculeaza media numerelor si trimite rezultatul inapoi parintelui.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
	if(argc<2)
	{
		printf("Introduceti un numar natural!\n");
		printf("Utilizare: ./ex2 20\n");
		return 1;
	}
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	int pid=fork();
	if(pid==-1)
	{
		perror("Fork esuat!\n");
		exit(1);
	}
	else if(pid==0)
	{
		close(fd1[1]);
		close(fd2[0]);
		int n;
		int i=0;
		float s=0;
		while(read(fd1[0],&n,sizeof(int)))
		{
			i++;
			s+=n;
		}
		close(fd1[0]);
		s=s/(float)(i);
		write(fd2[1],&s,sizeof(float));
		exit(0);
	}
	else
	{
		close(fd1[0]);
		close(fd2[1]);
		int n=atoi(argv[1]);
		for(int i=1;i<=n;i++)
			write(fd1[1],&i,sizeof(int));
		close(fd1[1]);
		float media;
		read(fd2[0],&media,sizeof(float));
		wait(NULL);
		printf("Media este %f\n",media);
	}
	return 0;
}
