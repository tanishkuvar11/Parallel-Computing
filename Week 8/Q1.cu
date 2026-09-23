#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>

__global__ void convolution1D(float *N, float *M, float *P, int width, int mask_width)
{
    int i=blockIdx.x * blockDim.x + threadIdx.x;
    if(i<width)
    {
        float sum=0;
        int start=i - mask_width / 2;
        for(int j=0; j<mask_width; j++)
        {
            if(start + j>=0 && start + j<width)
                sum+=N[start + j] * M[j];
        }
        P[i]=sum;
    }
}

int main()
{
    int width, mask_width;

    printf("Enter width of input array N: ");
    scanf("%d", &width);
    float *N=(float*)malloc(width * sizeof(float));
    float *P=(float*)malloc(width * sizeof(float));
    printf("Enter %d elements of N:\n", width);
    for(int i=0; i<width; i++)
        scanf("%f", &N[i]);

    printf("Enter mask_width: ");
    scanf("%d", &mask_width);
    float *M=(float*)malloc(mask_width * sizeof(float));
    printf("Enter %d elements of mask M:\n", mask_width);
    for(int i=0; i<mask_width; i++)
        scanf("%f", &M[i]);

    float *d_N, *d_M, *d_P;
    cudaMalloc((void**)&d_N, width * sizeof(float));
    cudaMalloc((void**)&d_M, mask_width * sizeof(float));
    cudaMalloc((void**)&d_P, width * sizeof(float));

    cudaMemcpy(d_N, N, width * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, M, mask_width * sizeof(float), cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(width + threads - 1) / threads;
    convolution1D<<<blocks, threads>>>(d_N, d_M, d_P, width, mask_width);

    cudaMemcpy(P, d_P, width * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Resultant array P:\n");
    for(int i=0; i<width; i++)
        printf("%.2f ", P[i]);
    printf("\n");

    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);
    free(N);
    free(M);
    free(P);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
