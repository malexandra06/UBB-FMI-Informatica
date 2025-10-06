/*Scrieti 2 programe C care comunica prin fifo. Cele doua procese isi vor trimite alternant unul celuilalt numere intre 1 si 10 (inclusiv) pana cand unul din ele trimite numarul 10. Afisati mesaje pe masura ce se trimit numere. Unul dintre procese va fi responsabil pentru crearea si stergerea canalelor fifo.*/

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
	mkfifo("./fifo1",0644);
	mkfifo("./fifo2",0644);
	f2 = open("./fifo2", O_WRONLY);
    	srandom(time(0));
    	int n = random() % 10 + 1;
    	printf("[PROCES A] Am trimis %d\n", n);
    	write(f2, &n, sizeof(int));
    	close(f2);
	if(n == 10) {
        printf("[PROCES A] Am generat 10, STOP!\n");
        unlink("./fifo1");
        unlink("./fifo2");
        return 0;
    }
	while(1)
	{
		f1=open("./fifo1",O_RDONLY);
		int n;
		n=read(f1,&n,sizeof(int));
		printf("[PROCES A] Am citit %d\n",n);
		close(f1);

		f2=open("./fifo2",O_WRONLY);
		n=random()%10+1;
		printf("[PROCES A] Am trimis %d\n",n);
                write(f2,&n,sizeof(int));
                close(f2);
		if(n==10)
		{
			printf("[PROCES A] Am generat 10, STOP!\n");
			break;
		}
	}

	unlink("./fifo1");
	unlink("./fifo2");
}
