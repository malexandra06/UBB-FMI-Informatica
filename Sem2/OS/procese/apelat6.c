#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
	(void)argc;
	(void)argv;
	int n1=atoi(argv[1]);
	int n2=atoi(argv[2]);
	int p=n1*n2;
	int fd=open(argv[3],O_WRONLY|O_CREAT|O_TRUNC,0644);
	char* nr=(char*)malloc(sizeof(char)*10);
	sprintf(nr,"%d",p);
	write(fd,nr,sizeof(nr));
	close(fd);	
	exit(0);
}
