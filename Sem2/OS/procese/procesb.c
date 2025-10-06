#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
int main()
{
	int f1,f2;
	srandom(time(0));
        while(1)
        {
                f1=open("./fifo2",O_RDONLY);
                int n;
                n=read(f1,&n,sizeof(int));
                printf("[PROCES B] Am citit %d\n",n);
                close(f1);
		if(n==10)
		{
			printf("[PROCES B] Am citit 10 STOP!\n");
			break;
		}
                f2=open("./fifo1",O_WRONLY);
                n=random()%10+1;
		printf("[PROCES B] Am trimis %d\n",n);
                write(f2,&n,sizeof(int));
                close(f2);
                if(n==10)
                {
                        printf("[PROCES b] Am generat 10, STOP!\n");
                        break;
                }
        }
}
