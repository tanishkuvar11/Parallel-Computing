/* 6. Implement a parallel program using OpenMP to perform vector addition, subtraction, and multiplication. 
	Demonstrate task level parallelism. Analyze the speedup and efficiency of the parallelized code. */
	
#include<stdio.h>
#include<omp.h>

int main()
{
    int n;

    printf("Enter size: ");
    scanf("%d", &n);

    int A[n], B[n], add[n], sub[n], mul[n];

    printf("Enter first vector:\n");
    for(int i=0; i<n; i++)
        scanf("%d", &A[i]);

    printf("Enter second vector:\n");
    for(int i=0; i<n; i++)
        scanf("%d", &B[i]);

    double start=omp_get_wtime();
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for(int i=0; i<n; i++)
                add[i]=A[i]+B[i];
        }

        #pragma omp section
        {
            for(int i=0; i<n; i++)
                sub[i]=A[i]-B[i];
        }

        #pragma omp section
        {
            for(int i=0; i<n; i++)
                mul[i]=A[i]*B[i];
        }
    }
    double end=omp_get_wtime();

    printf("\nAddition:\n");
    for(int i=0; i<n; i++)
        printf("%d ", add[i]);

    printf("\nSubtraction:\n");
    for(int i=0; i<n; i++)
        printf("%d ", sub[i]);

    printf("\nMultiplication:\n");
    for(int i=0; i<n; i++)
        printf("%d ", mul[i]);

    printf("\nTime=%f\n", end-start);

    printf("\nTanish Kuvar, 240962540\n");
}
