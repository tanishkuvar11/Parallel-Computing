/* 2. Implement an OpenMP program that creates a user-specified number of threads using the
omp_set_num_threads() runtime function and displays the Thread ID of each thread. */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argr, char* argv[])
{
	int n;
	printf("Enter number of threads: ");
	scanf("%d", &n);
	omp_set_num_threads(n);
	#pragma omp parallel
	{	
		int id=omp_get_thread_num();
		printf("Thread %d\n", id);
	}
	
	printf("Tanish Kuvar, 240962540\n");
	
	return 0;
}
