#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cuda_runtime.h>

__global__ void buildPattern(char *s, char *rs, int n)
{
    int i=blockIdx.x * blockDim.x + threadIdx.x;
    if(i<n)
    {
        int offset=i * n - (i * (i - 1)) / 2;
        for(int j=0; j<n - i; j++)
            rs[offset + j]=s[j];
    }
}

int main()
{
    char s[256];
    printf("Input string S: ");
    scanf("%s", s);

    int n=strlen(s);
    int total=n * (n + 1) / 2;
    char *rs=(char*)malloc(total + 1);

    char *d_s, *d_rs;
    cudaMalloc((void**)&d_s, n + 1);
    cudaMalloc((void**)&d_rs, total + 1);
    cudaMemcpy(d_s, s, n + 1, cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(n + threads - 1) / threads;
    buildPattern<<<blocks, threads>>>(d_s, d_rs, n);

    cudaMemcpy(rs, d_rs, total, cudaMemcpyDeviceToHost);
    rs[total]='\0';

    printf("Output string RS: %s\n", rs);

    cudaFree(d_s);
    cudaFree(d_rs);
    free(rs);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
