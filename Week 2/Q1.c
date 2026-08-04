/* 1. Implement an OpenMP program using the parallel for work-sharing construct to perform the addition of two matrices of size M × N. 
   Display the resultant matrix and the Thread ID responsible for computing each row. Compare the execution time of the serial and parallel 
   implementations and comment on the distribution of loop iterations among the threads. */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argr, char* argv[])
{
	int m, n;
	printf("Enter number of rows: ");
	scanf("%d", &m);
	printf("Enter number of columns: ");
	scanf("%d", &n);
	
	int a[m][n], b[m][n], c[m][n], d[m][n];
	printf("Enter elements of A:\n");
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
			scanf("%d", &a[i][j]);
	}
	
	printf("Enter elements of B:\n");
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
			scanf("%d", &b[i][j]);
	}
	
	double sstart=omp_get_wtime();
    for(int i=0; i<m; i++) 
    {
        for(int j=0; j<n; j++)
            c[i][j]=a[i][j]+b[i][j];
    }
    double send=omp_get_wtime();
   
	double pstart=omp_get_wtime();
	#pragma omp parallel for
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
			d[i][j]=a[i][j]+b[i][j];
		
		printf("Row %d: Thread %d\n", i+1, omp_get_thread_num());
	}
	double pend=omp_get_wtime();
	
	printf("\nResult:\n");
	for(int i=0; i<m; i++) 
    {
        for(int j=0; j<n; j++)
            printf("%d ", d[i][j]);
        printf("\n");
    }
    
    printf("Serial Time: %f\n", send-sstart);
    printf("Parallel Time: %f\n", pend-pstart);
    
    printf("\nTanish Kuvar, 240962540\n");
}
