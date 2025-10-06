#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define MAXIM 100

int main(int argc,char* argv[])
{
	FILE* fd=fopen(argv[2],"a");
	char oglindit[strlen(argv[1])+1];
	int k=0;
	for(int i=strlen(argv[1])-1;i>=0;i--)
		oglindit[k++]=argv[1][i];
	oglindit[k]='\0';
	fprintf(fd,"%s ",oglindit);
	fclose(fd);	
    	return 0;

}
