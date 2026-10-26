#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// Even elements -> replaced by their row sum
// Odd elements  -> replaced by their column sum
// One thread per element
__global__ void rowColSum(int *a, int *b, int m, int n)
{
    int row=blockIdx.y*blockDim.y+threadIdx.y;
    int col=blockIdx.x*blockDim.x+threadIdx.x;
    if (row<m && col<n)
    {
        int val=a[row*n+col];
        int sum=0;
        if (val%2==0)
        {
            for (int j=0; j<n; j++)
                sum+=a[row*n+j];
        }
        else
        {
            for (int i=0; i<m; i++)
                sum+=a[i*n+col];
        }
        b[row*n+col]=sum;
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

    printf("Enter elements of matrix A (%d x %d):\n", m, n);
    for (int i=0; i<m*n; i++)
        scanf("%d", &a[i]);

    int *d_a, *d_b;
    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

    dim3 threads(16, 16);
    dim3 blocks((n+threads.x-1)/threads.x, (m+threads.y-1)/threads.y);
    rowColSum<<<blocks, threads>>>(d_a, d_b, m, n);

    cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);

    printf("\nResultant matrix B:\n");
    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
            printf("%d\t", b[i*n+j]);
        printf("\n");
    }

    cudaFree(d_a);
    cudaFree(d_b);
    free(a);
    free(b);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
