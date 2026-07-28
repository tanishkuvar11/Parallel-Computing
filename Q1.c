/* 1. Implement an OpenMP program to determine and display the total number of threads
participating in a parallel region using the omp_get_num_threads() runtime function. */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argr, char* argv[])
{
	#pragma omp parallel
	{
		printf("%d\n", x);
	}
	
	printf("Tanish Kuvar, 240962540\n");
	
	return 0;
}
