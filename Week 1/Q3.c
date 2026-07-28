/* 3. Implement an OpenMP program to initialize all elements of a 5 × 5 matrix with consecutive
integers inside a parallel region using the parallel directive. Display the initialized matrix
and print the Thread ID responsible for initializing each row. */

// without parallel for

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argr, char* argv[])
{
	int matrix[5][5];
	#pragma omp parallel
	{
        for(int i=0; i<5; i++)
        {
            for(int j=0; j<5; j++)
                matrix[i][j] = 5*i+j;

            printf("Thread %d handled row %d\n", omp_get_thread_num(), i+1);
        }
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
