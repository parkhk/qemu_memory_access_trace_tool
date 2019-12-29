#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char InputData[1024]={0,};
	char ResultData[1024]={0,};
	FILE *fs0, *fs1, *fs2, *fs3, *fd;
	unsigned int flag = 1;


	fs0 = fopen("sample.trace_0","r");
	fs1 = fopen("sample.trace_1","r");
	fs2 = fopen("sample.trace_2","r");
	fs3 = fopen("sample.trace_3","r");
	fd = fopen("sample.merge","w");

	if( fs1 == NULL || fs2 == NULL )
	{
		perror("Error ");
		printf("Press any key to exit...\n");
//		getch();
		exit(EXIT_FAILURE);
	}

	while(flag){
		flag = 0;
		if(fgets(InputData,sizeof(InputData),fs0)!=NULL){
			flag = 1;
			fprintf(fd,"%s",InputData);    
		}
		if(fgets(InputData,sizeof(InputData),fs1)!=NULL){
			flag = 1;
			fprintf(fd,"%s",InputData);    
		}
		if(fgets(InputData,sizeof(InputData),fs2)!=NULL){
			flag = 1;
			fprintf(fd,"%s",InputData);    
		}
		if(fgets(InputData,sizeof(InputData),fs3)!=NULL){
			flag = 1;
			fprintf(fd,"%s",InputData);    
		}
	}
	fclose(fs0);
	fclose(fs1);
	fclose(fs2);
	fclose(fs3);
	fclose(fd);

	return 0;
}
