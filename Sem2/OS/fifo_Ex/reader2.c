#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int prim(int n)
{
	if(n<2)
		return 0;
	else if (n==2)
		return 1;
	else
		for(int i=2;i<=n/2;i++)
			if(n%i==0)
				return 0;
	return 1;
}
int main()
{
	int in=open("./fifo2",O_RDONLY);
	int n;
	read(in,&n,sizeof(int));
	if(prim(n)==1)
		printf("%s","Numarul este prim\n");
	else
		printf("%s","Numarul nu este prim\n");
	close(in);
	return 0;
}
