#include <stdio.h>
#include <stdlib.h>

#define  S_SIZE 0x2000

int init_test(unsigned long *j_1, unsigned long *j_2, unsigned long *j_3){

	int i;

	for(i = 0x0; i<S_SIZE; i++){
		j_1[i] = i;
		j_2[i] = i;
		j_3[i] = i;
	}

}

int main(int argc, char *argv[]){

	unsigned long i, v1;
	unsigned long p1, p2, p3;
	unsigned long j_1[S_SIZE];
	unsigned long j_2[S_SIZE];
	unsigned long j_3[S_SIZE];

//	printf("i = %p\nv1 = %p\ntest[0] = %p\ntest[1] = %p\ntest[2] = %p\n", &i, &v1, j_1, j_2, j_3);
	system("date");
	asm("nop");
	init_test(j_1, j_2, j_3);

	asm("nop");
	for(i = 0x0; i<S_SIZE; i++){
		j_3[i] += j_1[i]+j_2[i];
	}
	asm("nop");
	p1 = atoi(argv[1]);
	p2 = atoi(argv[2]);
	p3 = atoi(argv[3]);
	printf("i = 0x%lx\nv1 = 0x%lx\ntest[0][%d] = 0x%lx\ntest[1][%d] = 0x%lx\ntest[2][%d] = 0x%lx\n", i, v1, p1, j_1[p1], p2, j_2[p2], p3, j_3[p3]);
	system("date");

}
