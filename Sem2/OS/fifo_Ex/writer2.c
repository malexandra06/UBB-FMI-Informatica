#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	mkfifo("./fifo2",0644);
	int out=open("./fifo2",O_WRONLY);
	int n;
	printf("%s","Introduceti n=");
	scanf("%d",&n);
	write(out,&n,sizeof(int));
	close(out);
	unlink("./fifo2");
	return 0;
}
