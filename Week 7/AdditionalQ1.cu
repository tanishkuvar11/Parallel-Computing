#include <stdio.h>
#include <cuda_runtime.h>

__global__ void saxpy(float *x, float *y, float a, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
        y[i] = a * x[i] + y[i];
}

int main()
{
    int n;
    float a;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter alpha: ");
    scanf("%f", &a);

    float *x = new float[n];
    float *y = new float[n];

    printf("Enter x:\n");
    for (int i = 0; i < n; i++)
        scanf("%f", &x[i]);

    printf("Enter y:\n");
    for (int i = 0; i < n; i++)
        scanf("%f", &y[i]);

    float *dx, *dy;

    cudaMalloc(&dx, n * sizeof(float));
    cudaMalloc(&dy, n * sizeof(float));

    cudaMemcpy(dx, x, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dy, y, n * sizeof(float), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    saxpy<<<blocks, threads>>>(dx, dy, a, n);

    cudaMemcpy(y, dy, n * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Result:\n");
    for (int i = 0; i < n; i++)
        printf("%.2f ", y[i]);

    printf("\nTanish Kuvar, 240962540\n");

    cudaFree(dx);
    cudaFree(dy);

    delete[] x;
    delete[] y;

    return 0;
}
