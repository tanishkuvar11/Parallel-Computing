/* 5. Implement an OpenMP program to perform the addition of two matrices of size M×N using
the parallel for directive. Display the resultant matrix and indicate the Thread ID
responsible for computing each row (or element) of the result. */

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
	
	int a[m][n], b[m][n], c[m][n];
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
	
	printf("\n");
	#pragma omp parallel for
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
			c[i][j]=a[i][j]+b[i][j];
		
		printf("Row %d computed by Thread %d\n", i+1, omp_get_thread_num());
	}
	
	printf("\nC: \n");
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
			printf("%d ", c[i][j]);
			
		printf("\n");
	}
	
	printf("\nTanish Kuvar, 240962540\n");
}
