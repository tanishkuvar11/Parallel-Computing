#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void reverse(int *a, int *b, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
        b[n - 1 - i] = a[i];
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = new int[n];
    int *b = new int[n];

    for (int i = 0; i < n; i++)
        a[i] = rand() % 100;

    int *da, *db;

    cudaMalloc(&da, n * sizeof(int));
    cudaMalloc(&db, n * sizeof(int));

    cudaMemcpy(da, a, n * sizeof(int), cudaMemcpyHostToDevice);

    int threads = 32;
    int blocks = (n + threads - 1) / threads;

    reverse<<<blocks, threads>>>(da, db, n);

    cudaMemcpy(b, db, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Original array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\nReversed array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", b[i]);

    printf("\n\nTanish Kuvar, 240962540\n");

    cudaFree(da);
    cudaFree(db);

    delete[] a;
    delete[] b;

    return 0;
}
