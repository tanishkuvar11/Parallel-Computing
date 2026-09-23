#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>

__global__ void rankSort(int *a, int *b, int n)
{
    int i=blockIdx.x * blockDim.x + threadIdx.x;
    if(i<n)
    {
        int pos=0;
        for(int j=0; j<n; j++)
        {
            if(a[j]<a[i] || (a[j]==a[i] && j<i))
                pos++;
        }
        b[pos]=a[i];
    }
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *a=(int*)malloc(n * sizeof(int));
    int *b=(int*)malloc(n * sizeof(int));
    printf("Enter %d elements:\n", n);
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);

    int *d_a, *d_b;
    cudaMalloc((void**)&d_a, n * sizeof(int));
    cudaMalloc((void**)&d_b, n * sizeof(int));
    cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(n + threads - 1) / threads;
    rankSort<<<blocks, threads>>>(d_a, d_b, n);

    cudaMemcpy(b, d_b, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array:\n");
    for(int i=0; i<n; i++)
        printf("%d ", b[i]);
    printf("\n");

    cudaFree(d_a);
    cudaFree(d_b);
    free(a);
    free(b);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
