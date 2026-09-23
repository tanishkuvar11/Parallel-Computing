#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cuda_runtime.h>

__global__ void repeatString(char *sin, char *sout, int len, int N)
{
    int i=blockIdx.x * blockDim.x + threadIdx.x;
    if(i<len)
    {
        for(int k=0; k<N; k++)
            sout[k * len + i]=sin[i];
    }
}

int main()
{
    char sin[256];
    int N;
    printf("Enter input string Sin: ");
    scanf("%s", sin);
    printf("Enter N: ");
    scanf("%d", &N);

    int len=strlen(sin);
    int total=len * N;
    char *sout=(char*)malloc(total + 1);

    char *d_sin, *d_sout;
    cudaMalloc((void**)&d_sin, len + 1);
    cudaMalloc((void**)&d_sout, total + 1);
    cudaMemcpy(d_sin, sin, len + 1, cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(len + threads - 1) / threads;
    repeatString<<<blocks, threads>>>(d_sin, d_sout, len, N);

    cudaMemcpy(sout, d_sout, total, cudaMemcpyDeviceToHost);
    sout[total]='\0';

    printf("Output string Sout: %s\n", sout);

    cudaFree(d_sin);
    cudaFree(d_sout);
    free(sout);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
