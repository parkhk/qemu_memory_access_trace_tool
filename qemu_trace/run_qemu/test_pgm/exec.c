#include <stdio.h>
#include <unistd.h>

int main(){
	char buff[1000];
	sprintf(buff, "cat /proc/%d/status", getpid());
	system(buff);
	execlp("sort", "sort", "1G.txt", "-o", "sort_1G.txt", NULL);
}
