#include <stdio.h>
#include <stdlib.h>

int cmmdc(int a,int b)
{
	if(a==0 || b==0)
		return a;
	else if(a==1)
		return b;
	else if(b==1)
		return a;
	else
	{
		while(a!=b)
		{
			if(a>b)
				a=a-b;
			else
				b=b-a;			
		}
		return a;
	}
}

int main(int argc,char* argv[])
{
	(void)argc;
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	int c=cmmdc(a,b);
	FILE* fd=fopen(argv[3],"w");
	fprintf(fd,"%d",c);
	fclose(fd);
	exit(0);
}
