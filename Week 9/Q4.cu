#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// Row i (0-based) elements are raised to the power (i+1)
// One thread per element
__global__ void powerRows(int *a, int m, int n)
{
    int row=blockIdx.y*blockDim.y+threadIdx.y;
    int col=blockIdx.x*blockDim.x+threadIdx.x;
    if (row<m && col<n)
    {
        int val=a[row*n+col];
        int result=1;
        for (int k=0; k<=row; k++)
            result*=val;
        a[row*n+col]=result;
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

    printf("Enter elements of matrix A (%d x %d):\n", m, n);
    for (int i=0; i<m*n; i++)
        scanf("%d", &a[i]);

    int *d_a;
    cudaMalloc((void **)&d_a, size);
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

    dim3 threads(16, 16);
    dim3 blocks((n+threads.x-1)/threads.x, (m+threads.y-1)/threads.y);
    powerRows<<<blocks, threads>>>(d_a, m, n);

    cudaMemcpy(a, d_a, size, cudaMemcpyDeviceToHost);

    printf("\nResultant matrix:\n");
    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
            printf("%d\t", a[i*n+j]);
        printf("\n");
    }

    cudaFree(d_a);
    free(a);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
