#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// (a) Each row of resultant matrix computed by one thread
__global__ void addRowWise(int *a, int *b, int *c, int m, int n)
{
    int row=threadIdx.x;
    if (row<m)
    {
        for (int j=0; j<n; j++)
            c[row*n+j]=a[row*n+j]+b[row*n+j];
    }
}

// (b) Each column of resultant matrix computed by one thread
__global__ void addColWise(int *a, int *b, int *c, int m, int n)
{
    int col=threadIdx.x;
    if (col<n)
    {
        for (int i=0; i<m; i++)
            c[i*n+col]=a[i*n+col]+b[i*n+col];
    }
}

// (c) Each element of resultant matrix computed by one thread
__global__ void addElementWise(int *a, int *b, int *c, int m, int n)
{
    int row=threadIdx.y;
    int col=threadIdx.x;
    if (row<m && col<n)
        c[row*n+col]=a[row*n+col]+b[row*n+col];
}

void printMatrix(int *mat, int m, int n)
{
    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
            printf("%d\t", mat[i*n+j]);
        printf("\n");
    }
}

int main()
{
    int m, n;
    printf("Enter number of rows (M): ");
    scanf("%d", &m);
    printf("Enter number of columns (N): ");
    scanf("%d", &n);

    int size=m*n*sizeof(int);
    int *a=(int *)malloc(size);
    int *b=(int *)malloc(size);
    int *c=(int *)malloc(size);

    printf("Enter elements of matrix A:\n");
    for (int i=0; i<m*n; i++)
        scanf("%d", &a[i]);
    printf("Enter elements of matrix B:\n");
    for (int i=0; i<m*n; i++)
        scanf("%d", &b[i]);

    int *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    // (a) Row-wise
    addRowWise<<<1, m>>>(d_a, d_b, d_c, m, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    printf("\n(a) Result (one thread per row):\n");
    printMatrix(c, m, n);

    // (b) Column-wise
    cudaMemset(d_c, 0, size);
    addColWise<<<1, n>>>(d_a, d_b, d_c, m, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    printf("\n(b) Result (one thread per column):\n");
    printMatrix(c, m, n);

    // (c) Element-wise
    cudaMemset(d_c, 0, size);
    dim3 threads(n, m);
    addElementWise<<<1, threads>>>(d_a, d_b, d_c, m, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    printf("\n(c) Result (one thread per element):\n");
    printMatrix(c, m, n);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(a);
    free(b);
    free(c);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
