#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main()
{
	mkfifo("./fifo3",0644);
	int out=open("./fifo3",O_WRONLY);
	char c,s[100];
	printf("Introduceti caracterul c=");
	scanf("%c",&c);
	printf("Introduceti sirul s\n");
	scanf("%s",s);
	write(out,&c,sizeof(char));
	write(out,s,sizeof(char)*strlen(s));
	close(out);
	unlink("./fifo3");
	return 0;
}
