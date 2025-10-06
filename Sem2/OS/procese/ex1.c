/*Scrieti un program C care creeaza n procese fiu. Fiecare proces fiu va afisa propriul PID si PID-ul procesului parinte, iar procesul parinte va afisa propriul PID si PID-urile tuturor proceselor sale fiu.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	if(argc<2)
	{
		printf("Introduceti un numar!\n");
		printf("Utilizare: ./ex1 10\n");
		return 1;
	}
	
	int n=atoi(argv[1]);
	for(int i=1;i<=n;i++)
	{
		int pid=fork();
		if(pid==-1)
		{
			perror("Fork esuat!\n");
			exit(1);
		}
		else if(pid==0)
		{
			printf("[CHILD] MyPID: %d; ParentPID: %d\n",getpid(),getppid());
			exit(0);
		}
		else
		{
			printf("[PARENT] MyPID: %d; ChildPID: %d\n",getpid(),pid);
		}	
	}
	for(int i=1;i<=n;i++)
		wait(NULL);
	return 0;
}
