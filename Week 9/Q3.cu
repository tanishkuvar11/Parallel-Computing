#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// Sparse Matrix - Vector multiplication using CSR format
// One thread computes one row of the output vector
__global__ void spmvCSR(int *values, int *colIdx, int *rowPtr, int *x, int *y, int m)
{
    int row=blockIdx.x*blockDim.x+threadIdx.x;
    if (row<m)
    {
        int sum=0;
        for (int k=rowPtr[row]; k<rowPtr[row+1]; k++)
            sum+=values[k]*x[colIdx[k]];
        y[row]=sum;
    }
}

int main()
{
    int m, n;
    printf("Enter number of rows (M): ");
    scanf("%d", &m);
    printf("Enter number of columns (N): ");
    scanf("%d", &n);

    int *mat=(int *)malloc(m*n*sizeof(int));
    printf("Enter elements of sparse matrix (%d x %d):\n", m, n);
    for (int i=0; i<m*n; i++)
        scanf("%d", &mat[i]);

    int *x=(int *)malloc(n*sizeof(int));
    printf("Enter elements of vector (size %d):\n", n);
    for (int i=0; i<n; i++)
        scanf("%d", &x[i]);

    // Count non-zero elements
    int nnz=0;
    for (int i=0; i<m*n; i++)
        if (mat[i]!=0)
            nnz++;

    // Build CSR representation in host code
    int *values=(int *)malloc((nnz>0 ? nnz : 1)*sizeof(int));
    int *colIdx=(int *)malloc((nnz>0 ? nnz : 1)*sizeof(int));
    int *rowPtr=(int *)malloc((m+1)*sizeof(int));

    int k=0;
    rowPtr[0]=0;
    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (mat[i*n+j]!=0)
            {
                values[k]=mat[i*n+j];
                colIdx[k]=j;
                k++;
            }
        }
        rowPtr[i+1]=k;
    }

    printf("\nCSR Representation:\n");
    printf("Values : ");
    for (int i=0; i<nnz; i++)
        printf("%d ", values[i]);
    printf("\nColIdx : ");
    for (int i=0; i<nnz; i++)
        printf("%d ", colIdx[i]);
    printf("\nRowPtr : ");
    for (int i=0; i<=m; i++)
        printf("%d ", rowPtr[i]);
    printf("\n");

    int *d_values, *d_colIdx, *d_rowPtr, *d_x, *d_y;
    cudaMalloc((void **)&d_values, (nnz>0 ? nnz : 1)*sizeof(int));
    cudaMalloc((void **)&d_colIdx, (nnz>0 ? nnz : 1)*sizeof(int));
    cudaMalloc((void **)&d_rowPtr, (m+1)*sizeof(int));
    cudaMalloc((void **)&d_x, n*sizeof(int));
    cudaMalloc((void **)&d_y, m*sizeof(int));

    cudaMemcpy(d_values, values, nnz*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_colIdx, colIdx, nnz*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_rowPtr, rowPtr, (m+1)*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, n*sizeof(int), cudaMemcpyHostToDevice);

    int threadsPerBlock=256;
    int blocks=(m+threadsPerBlock-1)/threadsPerBlock;
    spmvCSR<<<blocks, threadsPerBlock>>>(d_values, d_colIdx, d_rowPtr, d_x, d_y, m);

    int *y=(int *)malloc(m*sizeof(int));
    cudaMemcpy(y, d_y, m*sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nResultant vector (A * x):\n");
    for (int i=0; i<m; i++)
        printf("%d\n", y[i]);

    cudaFree(d_values);
    cudaFree(d_colIdx);
    cudaFree(d_rowPtr);
    cudaFree(d_x);
    cudaFree(d_y);
    free(mat);
    free(x);
    free(y);
    free(values);
    free(colIdx);
    free(rowPtr);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
