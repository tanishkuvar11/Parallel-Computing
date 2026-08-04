/* 2. Implement an OpenMP program to read a matrix A of size 5 × 5 and produce matrix B according to the specified transformation:
	Principal diagonal = 0
	Elements below the diagonal = maximum value of the corresponding row in A
	Elements above the diagonal = minimum value of the corresponding row in A */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argr, char* argv[])
{
	int a[5][5], b[5][5];
	printf("Enter elements of A:\n");
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
			scanf("%d", &a[i][j]);
	}

	#pragma omp parallel for
	for(int i=0; i<5; i++)
	{
		int max=a[i][0];
		int min=a[i][0];
		for(int j=1; j<5; j++)
		{
			if(a[i][j]<min)
				min=a[i][j];
			else if(a[i][j]>max)
				max=a[i][j];
		}
		
		for(int j=0; j<5; j++)
		{
			if(i>j)
				b[i][j]=max;
			else if(i<j)
				b[i][j]=min;
			else
				b[i][j]=0;
		}
	}
	
	printf("\n\nResult:\n");
	for(int i=0; i<5; i++) 
    {
        for(int j=0; j<5; j++)
            printf("%d ", b[i][j]);
        printf("\n");
    }
    
    printf("\nTanish Kuvar, 240962540\n");
}
				
