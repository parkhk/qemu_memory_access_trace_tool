#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define FILE_SIZE 1024*1024

int main()
{
	unsigned int i = 0;
	unsigned int j = 0, tmp;
	char buff[32];
	int fd;

	srand(time(NULL));
	fd = open("open.txt", O_CREAT|O_WRONLY);
	while(i < FILE_SIZE*(1024/32))
	{
		for(j=0;j<32;j++){
			tmp = rand()%96;
			buff[j] = tmp+32;
		}
		buff[31] = '\n';
		write(fd, buff, 32);
		i++;
	}
}
