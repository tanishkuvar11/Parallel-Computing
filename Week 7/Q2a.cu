#include<stdio.h>
#include<cuda.h>

__global__ void vectorAdd(int*A,int*B,int*C,int N)
{
    int i=threadIdx.x;

    if(i<N)
        C[i]=A[i]+B[i];
}

int main()
{
    int N;

    printf("Enter N: ");
    scanf("%d",&N);

    int*A,*B,*C;

    cudaMallocManaged(&A,N*sizeof(int));
    cudaMallocManaged(&B,N*sizeof(int));
    cudaMallocManaged(&C,N*sizeof(int));

    printf("Enter elements of vector A:\n");
    for(int i=0;i<N;i++)
        scanf("%d",&A[i]);

    printf("Enter elements of vector B:\n");
    for(int i=0;i<N;i++)
        scanf("%d",&B[i]);

    vectorAdd<<<1,N>>>(A,B,C,N);

    cudaDeviceSynchronize();

    printf("Result:\n");
    for(int i=0;i<N;i++)
        printf("%d ",C[i]);

    printf("\n\nTanish Kuvar, 240962540\n");

    cudaFree(A);
    cudaFree(B);
    cudaFree(C);

    return 0;
}
