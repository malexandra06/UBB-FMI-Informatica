#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	mkfifo("./fifo1",0644);
	int in=open("./fifo1",O_RDONLY);
	int n;
	read(in,&n,sizeof(int));
	close(in);
	if(n%2==0)
		printf("%s","Numarul este par\n");
	else
		printf("%s","Numarul este impar\n");
	return 0;
}
