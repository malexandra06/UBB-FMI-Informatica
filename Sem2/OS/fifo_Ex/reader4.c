#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
	int in=open("./fifo4",O_RDONLY);
	int n1,n2;
	read(in,&n1,sizeof(int));
	read(in,&n2,sizeof(int));
	close(in);
	n1+=n2;
	int out=open("./fifo44",O_WRONLY);
	write(out,&n1,sizeof(int));
	close(out);
	return 0;
}
