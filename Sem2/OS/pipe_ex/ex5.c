/*Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte dintr-un fişier de tip text două numere întregi pe care le trimite prin pipe procesului copil, iar procesul copil returnează prin pipe suma lor.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	(void)argv;
	if(argc<2)
	{
		printf("Introduceti un nume de fisier pentru numere\n");
		exit(1);
	}
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	if(fork()==0)
	{
		close(fd1[1]);
		close(fd2[0]);
		int n1,n2;
		read(fd1[0],&n1,sizeof(int));
		read(fd1[0],&n2,sizeof(int));
		close(fd1[0]);
		n1+=n2;
		write(fd2[1],&n1,sizeof(int));
		close(fd2[1]);
		exit(0);
	}
	else
	{
		close(fd1[0]);
		close(fd2[1]);
		FILE* descr=fopen(argv[1],"r");
		int n1,n2;
		fscanf(descr,"%d",&n1);
		fscanf(descr,"%d",&n2);
		fclose(descr);
		write(fd1[1],&n1,sizeof(int));
		write(fd1[1],&n2,sizeof(int));
		close(fd1[1]);
		int s;
		read(fd2[0],&s,sizeof(int));
		close(fd2[0]);
		wait(NULL);
		printf("Suma este %d\n",s);
		exit(0);
	}
}
