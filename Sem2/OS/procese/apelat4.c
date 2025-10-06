#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int cmmdc(int a,int b)
{
	while(a!=b)
	{
		if(a<b)
			b=b-a;
		else
			a=a-b;
	}
	return a;
}

int cmmmc(int a,int b)
{
	if(a==0 || b==0)
		return 0;
	else if(a==1)
		return b;
	else if(b==1)
		return a;
	else
		return a*b/cmmdc(a,b);
}

int main(int argc,char* argv[])
{
	(void)argc;
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	int fd=open(argv[3],O_WRONLY|O_CREAT|O_TRUNC,0644);
	if(fd==-1)
	{
		perror("eroare la deschiderea fisierului");
		exit(1);
	}
	int result=cmmmc(a,b);
	char buffer[50];
        sprintf(buffer, "%d", result);
	write(fd,buffer,strlen(buffer));
	close(fd);
	exit(0);
}
