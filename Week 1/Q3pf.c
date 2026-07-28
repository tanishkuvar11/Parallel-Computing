/* 3. Implement an OpenMP program to initialize all elements of a 5 × 5 matrix with consecutive
integers inside a parallel region using the parallel directive. Display the initialized matrix
and print the Thread ID responsible for initializing each row. */

// with parallel for

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argr, char* argv[])
{
	int matrix[5][5];
	#pragma omp parallel for
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
			matrix[i][j]=i*5+j;
		printf("Thread ID for row %d: %d\n", i+1, omp_get_thread_num());
	}
	
	printf("\n");
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
	
	printf("Tanish Kuvar, 240962540\n");
}
