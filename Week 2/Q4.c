/* 4. Implement an OpenMP program to perform matrix-vector multiplication. 
	Record the effect of increasing matrix size on execution time. */
	
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main()
{
    int m, n;

    printf("Enter rows and columns: ");
    scanf("%d%d", &m, &n);

    int A[m][n], x[n], y[m];

    printf("Enter matrix:\n");
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter vector:\n");
    for(int i=0; i<n; i++)
        scanf("%d", &x[i]);

    double start=omp_get_wtime();
    #pragma omp parallel for
    for(int i=0; i<m; i++)
    {
        y[i]=0;
        for(int j=0; j<n; j++)
            y[i]+=A[i][j]*x[j];
    }
    double end=omp_get_wtime();

    printf("\nResult:\n");
    for(int i=0; i<m; i++)
        printf("%d\n", y[i]);

    printf("\nTime=%f\n", end-start);

    printf("\nTanish Kuvar, 240962540\n");
}
