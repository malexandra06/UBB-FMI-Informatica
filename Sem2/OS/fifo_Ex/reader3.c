#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int aparitii(char c,char s[100])
{
	int nr=0;
	for(int i=0;i<(int)strlen(s);i++)
		if(s[i]==c)
			nr++;
	return nr;
}


int main()
{
	int in=open("./fifo3",O_RDONLY);
	char s[100],c;
	read(in,&c,sizeof(char));
	read(in,s,sizeof(char)*100);
	close(in);
	int nr=aparitii(c,s);
	printf("Numarul de aparitii este %d\n",nr);
	return 0;
}
