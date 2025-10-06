#include <stdio.h>
#include <stdlib.h>
#define MAXIM 100
int main(int argc,char *argv[])
{
	int n[MAXIM];
	for(int i=1;i<argc;i++)
	{
		n[i]=atoi(argv[i]);
	}
	for(int i=1;i<argc-1;i++)
		if(n[i]!=n[i+1])
			exit(1);	
	exit(0);
}
