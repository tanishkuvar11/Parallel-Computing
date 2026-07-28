/* 6. Implement an OpenMP program to compute the sum of elements of a large array in parallel
using the parallel for directive. Measure and display the execution time of the parallel
program using the omp_get_wtime() runtime function and compare it with the
corresponding serial implementation. */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argr, char* argv[])
{
	int a[1000000];
	for(int i=0; i<1000000; i++)
		a[i]=1;
		
	int sum=0;
	printf("Parallel: \n");
	double pstart=omp_get_wtime();
	#pragma omp parallel for
	for(int i=0; i<1000000; i++)
		sum+=a[i];
	double pend=omp_get_wtime();
	printf("Sum: %d\n", sum);
	printf("Time: %f\n", pend-pstart);
	
	sum=0;
	printf("\nSerial: \n");
	double sstart=omp_get_wtime();
	for(int i=0; i<1000000; i++)
		sum+=a[i];
	double send=omp_get_wtime();
	printf("Sum: %d\n", sum);
	printf("Time: %f\n", send-sstart);

	printf("\nTanish Kuvar, 240962540\n");
}
