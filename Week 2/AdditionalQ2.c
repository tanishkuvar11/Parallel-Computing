/* 2. Implement an OpenMP program that performs the addition of two one-dimensional arrays using the parallel for directive. */

#include<stdio.h>
#include<omp.h>

int main()
{
    int n;

    printf("Enter size: ");
    scanf("%d", &n);

    int A[n], B[n], C[n];

    printf("Enter first array:\n");
    for(int i=0; i<n; i++)
        scanf("%d", &A[i]);

    printf("Enter second array:\n");
    for(int i=0; i<n; i++)
        scanf("%d", &B[i]);

    #pragma omp parallel for
    for(int i=0; i<n; i++)
        C[i]=A[i]+B[i];

    printf("Result:\n");
    for(int i=0; i<n; i++)
        printf("%d ", C[i]);

    printf("\nTanish Kuvar, 240962540\n");
}
