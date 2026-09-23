#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<cuda.h>

__global__ void euclideanDistance(float*A,float*B,float*C,int N)
{
    int i=blockIdx.x*blockDim.x+threadIdx.x;

    if(i<N)
        C[i]=(A[i]-B[i])*(A[i]-B[i]);
}

int main()
{
    int N;

    printf("Enter N: ");
    scanf("%d",&N);

    float*A,*B,*C;

    cudaMallocManaged(&A,N*sizeof(float));
    cudaMallocManaged(&B,N*sizeof(float));
    cudaMallocManaged(&C,N*sizeof(float));

    // Random initialization
    for(int i=0;i<N;i++)
    {
        A[i]=(float)rand()/RAND_MAX;
        B[i]=(float)rand()/RAND_MAX;
    }

    printf("Vector A:\n");
    for(int i=0;i<N;i++)
        printf("%f ",A[i]);

    printf("\n\nVector B:\n");
    for(int i=0;i<N;i++)
        printf("%f ",B[i]);

        printf("\n");

    int threads=256;
    int blocks=(N+threads-1)/threads;

    euclideanDistance<<<blocks,threads>>>(A,B,C,N);

    cudaDeviceSynchronize();

    float sum=0;

    for(int i=0;i<N;i++)
        sum+=C[i];

    float distance=sqrt(sum);

    printf("Euclidean Distance = %f\n",distance);

    printf("\nTanish Kuvar, 240962540\n");

    cudaFree(A);
    cudaFree(B);
    cudaFree(C);

    return 0;
}
