#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cuda_runtime.h>

__global__ void reverseWords(char *s, int n)
{
    int i=blockIdx.x * blockDim.x + threadIdx.x;
    if(i<n && s[i]!=' ' && (i==0 || s[i - 1]==' '))
    {
        int end=i;
        while(end + 1<n && s[end + 1]!=' ')
            end++;
        int l=i, r=end;
        while(l<r)
        {
            char temp=s[l];
            s[l]=s[r];
            s[r]=temp;
            l++;
            r--;
        }
    }
}

int main()
{
    char str[1024];
    printf("Enter a string of N words: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")]='\0';

    int n=strlen(str);

    char *d_s;
    cudaMalloc((void**)&d_s, n + 1);
    cudaMemcpy(d_s, str, n + 1, cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(n + threads - 1) / threads;
    reverseWords<<<blocks, threads>>>(d_s, n);

    cudaMemcpy(str, d_s, n + 1, cudaMemcpyDeviceToHost);

    printf("String with each word reversed: %s\n", str);

    cudaFree(d_s);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
