#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// Each thread takes one character of A and writes it B[idx] times
// into STR. Its starting position is the sum of all earlier B values.
__global__ void repeatChars(char *a, int *b, char *str, int total)
{
    int idx=blockIdx.x*blockDim.x+threadIdx.x;
    if (idx<total)
    {
        int start=0;
        for (int k=0; k<idx; k++)
            start+=b[k];
        for (int r=0; r<b[idx]; r++)
            str[start+r]=a[idx];
    }
}

int main()
{
    int m, n;
    printf("Enter number of rows (M): ");
    scanf("%d", &m);
    printf("Enter number of columns (N): ");
    scanf("%d", &n);

    int total=m*n;
    char *a=(char *)malloc(total*sizeof(char));
    int *b=(int *)malloc(total*sizeof(int));

    printf("Enter characters of matrix A (%d x %d):\n", m, n);
    for (int i=0; i<total; i++)
        scanf(" %c", &a[i]);

    printf("Enter integers of matrix B (%d x %d):\n", m, n);
    for (int i=0; i<total; i++)
        scanf("%d", &b[i]);

    int len=0;
    for (int i=0; i<total; i++)
        len+=b[i];

    char *str=(char *)malloc((len+1)*sizeof(char));

    char *d_a, *d_str;
    int *d_b;
    cudaMalloc((void **)&d_a, total*sizeof(char));
    cudaMalloc((void **)&d_b, total*sizeof(int));
    cudaMalloc((void **)&d_str, (len+1)*sizeof(char));

    cudaMemcpy(d_a, a, total*sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, total*sizeof(int), cudaMemcpyHostToDevice);

    int threadsPerBlock=256;
    int blocks=(total+threadsPerBlock-1)/threadsPerBlock;
    repeatChars<<<blocks, threadsPerBlock>>>(d_a, d_b, d_str, total);

    cudaMemcpy(str, d_str, len*sizeof(char), cudaMemcpyDeviceToHost);
    str[len]='\0';

    printf("\nOutput String STR: %s\n", str);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_str);
    free(a);
    free(b);
    free(str);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
