#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	(void)argc;
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    	if (fd < 0) {
        	perror("Eroare la deschiderea fișierului");
        	exit(1);
    	}
	char oglindit[100];
	int k=0;
	for(int i=strlen(argv[2])-1;i>=0;i--)
		oglindit[k++]=argv[2][i];
	oglindit[k]='\0';
	write(fd,oglindit,strlen(oglindit));
	close(fd);
	exit(0);	
}
