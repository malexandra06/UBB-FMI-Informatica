#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	mkfifo("./fifo1",0644);
	int out=open("./fifo1",O_WRONLY);
	int n;
	printf("%s","Introduceti n=");
	scanf("%d",&n);
	write(out,&n,sizeof(int));
	close(out);
	unlink("./fifo1");
	return 0;
}
