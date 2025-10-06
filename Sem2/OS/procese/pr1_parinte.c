#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char* argv[])
{
	if(fork()==0)
	{
		execv("./pr1",argv);
	}
	int status;
	wait(&status);
	switch (WEXITSTATUS(status)) {
            case 0: printf("Numerele sunt egale!\n");   break;
            case 1: printf("Numerele nu sunt egale!\n"); break;
           }
	return 0;
}
