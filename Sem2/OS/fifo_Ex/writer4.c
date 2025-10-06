#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	mkfifo("./fifo4",0644);
	mkfifo("./fifo44",0644);
	int out=open("./fifo4",O_WRONLY);
	int n1,n2;
	printf("Introduceti n1=");
	scanf("%d",&n1);
	printf("Introduceti n2=");
	scanf("%d",&n2);
	write(out,&n1,sizeof(int));
	write(out,&n2,sizeof(int));
	close(out);
	int in=open("./fifo44",O_RDONLY);
	int s;
	read(in,&s,sizeof(int));
	close(in);
	unlink("./fifo4");
	unlink("./fifo44");
	printf("Suma este %d\n",s);
	return 0;
}
