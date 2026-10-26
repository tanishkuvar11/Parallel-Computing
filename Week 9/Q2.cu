#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// A is m x n, B is n x p, C is m x p

// (a) Each row of resultant matrix computed by one thread
__global__ void mulRowWise(int *a, int *b, int *c, int m, int n, int p)
{
    int row=threadIdx.x;
    if (row<m)
    {
        for (int j=0; j<p; j++)
        {
            int sum=0;
            for (int k=0; k<n; k++)
                sum+=a[row*n+k]*b[k*p+j];
            c[row*p+j]=sum;
        }
    }
}

// (b) Each column of resultant matrix computed by one thread
__global__ void mulColWise(int *a, int *b, int *c, int m, int n, int p)
{
    int col=threadIdx.x;
    if (col<p)
    {
        for (int i=0; i<m; i++)
        {
            int sum=0;
            for (int k=0; k<n; k++)
                sum+=a[i*n+k]*b[k*p+col];
            c[i*p+col]=sum;
        }
    }
}

// (c) Each element of resultant matrix computed by one thread
__global__ void mulElementWise(int *a, int *b, int *c, int m, int n, int p)
{
    int row=threadIdx.y;
    int col=threadIdx.x;
    if (row<m && col<p)
    {
        int sum=0;
        for (int k=0; k<n; k++)
            sum+=a[row*n+k]*b[k*p+col];
        c[row*p+col]=sum;
    }
}

void printMatrix(int *mat, int r, int cl)
{
    for (int i=0; i<r; i++)
    {
        for (int j=0; j<cl; j++)
            printf("%d\t", mat[i*cl+j]);
        printf("\n");
    }
}

int main()
{
    int m, n, p;
    printf("Enter rows and columns of matrix A (M N): ");
    scanf("%d %d", &m, &n);
    printf("Enter columns of matrix B (P), B is %d x P: ", n);
    scanf("%d", &p);

    int sizeA=m*n*sizeof(int);
    int sizeB=n*p*sizeof(int);
    int sizeC=m*p*sizeof(int);

    int *a=(int *)malloc(sizeA);
    int *b=(int *)malloc(sizeB);
    int *c=(int *)malloc(sizeC);

    printf("Enter elements of matrix A (%d x %d):\n", m, n);
    for (int i=0; i<m*n; i++)
        scanf("%d", &a[i]);
    printf("Enter elements of matrix B (%d x %d):\n", n, p);
    for (int i=0; i<n*p; i++)
        scanf("%d", &b[i]);

    int *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, sizeA);
    cudaMalloc((void **)&d_b, sizeB);
    cudaMalloc((void **)&d_c, sizeC);

    cudaMemcpy(d_a, a, sizeA, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeB, cudaMemcpyHostToDevice);

    // (a) Row-wise
    mulRowWise<<<1, m>>>(d_a, d_b, d_c, m, n, p);
    cudaMemcpy(c, d_c, sizeC, cudaMemcpyDeviceToHost);
    printf("\n(a) Result (one thread per row):\n");
    printMatrix(c, m, p);

    // (b) Column-wise
    cudaMemset(d_c, 0, sizeC);
    mulColWise<<<1, p>>>(d_a, d_b, d_c, m, n, p);
    cudaMemcpy(c, d_c, sizeC, cudaMemcpyDeviceToHost);
    printf("\n(b) Result (one thread per column):\n");
    printMatrix(c, m, p);

    // (c) Element-wise
    cudaMemset(d_c, 0, sizeC);
    dim3 threads(p, m);
    mulElementWise<<<1, threads>>>(d_a, d_b, d_c, m, n, p);
    cudaMemcpy(c, d_c, sizeC, cudaMemcpyDeviceToHost);
    printf("\n(c) Result (one thread per element):\n");
    printMatrix(c, m, p);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(a);
    free(b);
    free(c);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
