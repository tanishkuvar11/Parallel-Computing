#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cuda_runtime.h>

__global__ void replaceVowels(int *s, int n)
{
    int i=blockIdx.x * blockDim.x + threadIdx.x;
    if(i<n)
    {
        int c=s[i];
        if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
           c=='A' || c=='E' || c=='I' || c=='O' || c=='U')
        {
            atomicExch(&s[i], (int)'*');
        }
    }
}

int main()
{
    char str[1024];
    printf("Input String S: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")]='\0';

    int n=strlen(str);
    int *h=(int*)malloc(n * sizeof(int));
    for(int i=0; i<n; i++)
        h[i]=(int)str[i];

    int *d_s;
    cudaMalloc((void**)&d_s, n * sizeof(int));
    cudaMemcpy(d_s, h, n * sizeof(int), cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(n + threads - 1) / threads;
    replaceVowels<<<blocks, threads>>>(d_s, n);

    cudaMemcpy(h, d_s, n * sizeof(int), cudaMemcpyDeviceToHost);

    char rs[1024];
    for(int i=0; i<n; i++)
        rs[i]=(char)h[i];
    rs[n]='\0';

    printf("Output String RS: %s\n", rs);

    cudaFree(d_s);
    free(h);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
