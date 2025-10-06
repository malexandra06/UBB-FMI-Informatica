#include <stdlib.h>

int main(int argc,char* argv[])
{
	int sir[argc];
	int p=1;
	for(int i=1;i<argc;i++)
	{
		sir[i]=atoi(argv[i]);
		p=p*sir[i];
	}
	if(p>0)
		exit(0);
	else if(p==0)
		exit(2);
	else
		exit(1);
}
