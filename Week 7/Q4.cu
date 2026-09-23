#include <stdio.h>
#include <cuda_runtime.h>

__global__ void sine(float *a, float *b, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
        b[i] = sin(a[i]);
}

int main()
{
    int n;

    printf("Enter number of angles: ");
    scanf("%d", &n);

    float *a = new float[n];
    float *b = new float[n];

    printf("Enter angles in radians:\n");

    for (int i = 0; i < n; i++)
        scanf("%f", &a[i]);

    float *da, *db;

    cudaMalloc(&da, n * sizeof(float));
    cudaMalloc(&db, n * sizeof(float));

    cudaMemcpy(da, a, n * sizeof(float), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    sine<<<blocks, threads>>>(da, db, n);

    cudaMemcpy(b, db, n * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Sine values:\n");

    for (int i = 0; i < n; i++)
        printf("%.4f ", b[i]);

    printf("\n");
    printf("\nTanish Kuvar, 240962540\n");

    cudaFree(da);
    cudaFree(db);

    delete[] a;
    delete[] b;

    return 0;
}
