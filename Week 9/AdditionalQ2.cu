#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__device__ long long factorial(int x)
{
    long long f=1;
    for (int i=2; i<=x; i++)
        f*=i;
    return f;
}

__device__ long long digitSum(int x)
{
    if (x<0)
        x=-x;
    long long s=0;
    while (x>0)
    {
        s+=x%10;
        x/=10;
    }
    return s;
}

// Principal diagonal -> 0
// Above diagonal     -> factorial of element
// Below diagonal     -> sum of digits of element
// One thread per element
__global__ void transform(int *a, long long *b, int n)
{
    int row=blockIdx.y*blockDim.y+threadIdx.y;
    int col=blockIdx.x*blockDim.x+threadIdx.x;
    if (row<n && col<n)
    {
        int val=a[row*n+col];
        if (row==col)
            b[row*n+col]=0;
        else if (row<col)
            b[row*n+col]=factorial(val);
        else
            b[row*n+col]=digitSum(val);
    }
}

int main()
{
    int n;
    printf("Enter size of square matrix (N): ");
    scanf("%d", &n);

    int *a=(int *)malloc(n*n*sizeof(int));
    long long *b=(long long *)malloc(n*n*sizeof(long long));

    printf("Enter elements of matrix A (%d x %d):\n", n, n);
    for (int i=0; i<n*n; i++)
        scanf("%d", &a[i]);

    int *d_a;
    long long *d_b;
    cudaMalloc((void **)&d_a, n*n*sizeof(int));
    cudaMalloc((void **)&d_b, n*n*sizeof(long long));
    cudaMemcpy(d_a, a, n*n*sizeof(int), cudaMemcpyHostToDevice);

    dim3 threads(16, 16);
    dim3 blocks((n+threads.x-1)/threads.x, (n+threads.y-1)/threads.y);
    transform<<<blocks, threads>>>(d_a, d_b, n);

    cudaMemcpy(b, d_b, n*n*sizeof(long long), cudaMemcpyDeviceToHost);

    printf("\nResultant matrix:\n");
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            printf("%lld\t", b[i*n+j]);
        printf("\n");
    }

    cudaFree(d_a);
    cudaFree(d_b);
    free(a);
    free(b);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
