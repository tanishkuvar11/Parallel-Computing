/* 4. Implement an OpenMP program to perform the addition of two one-dimensional arrays of
size N using the parallel for directive. Display the resulting array and identify the Thread
ID that computes each array element. */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argr, char* argv[])
{
	int n;
	printf("Enter number of elements: ");
	scanf("%d", &n);
	
	int a[n], b[n], c[n];
	printf("Enter elements of A: ");
	for(int i=0; i<n; i++)
		scanf("%d", &a[i]);
	
	printf("Enter elements of B: ");
	for(int i=0; i<n; i++)
		scanf("%d", &b[i]);

	printf("\n");
	#pragma omp parallel for
	for(int i=0; i<n; i++)
	{
		c[i]=a[i]+b[i];
		printf("Element %d computed by Thread %d\n", i+1, omp_get_thread_num());
	}
	
	printf("\nC: ");
	for(int i=0; i<n; i++)
		printf("%d ", c[i]);
	printf("\n");
	
	printf("Tanish Kuvar, 240962540\n");
}
