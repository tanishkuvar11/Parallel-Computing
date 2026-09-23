#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>

__global__ void oddEvenSort(int *a, int n, int phase)
{
    int i=blockIdx.x * blockDim.x + threadIdx.x;
    int idx=2 * i + (phase % 2);
    if(idx + 1<n)
    {
        if(a[idx]>a[idx + 1])
        {
            int temp=a[idx];
            a[idx]=a[idx + 1];
            a[idx + 1]=temp;
        }
    }
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *a=(int*)malloc(n * sizeof(int));
    printf("Enter %d elements:\n", n);
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);

    int *d_a;
    cudaMalloc((void**)&d_a, n * sizeof(int));
    cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);

    int pairs=(n + 1) / 2;
    int threads=256;
    int blocks=(pairs + threads - 1) / threads;

    for(int phase=0; phase<n; phase++)
    {
        oddEvenSort<<<blocks, threads>>>(d_a, n, phase);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(a, d_a, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array:\n");
    for(int i=0; i<n; i++)
        printf("%d ", a[i]);
    printf("\n");

    cudaFree(d_a);
    free(a);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
