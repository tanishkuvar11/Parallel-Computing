#include <stdio.h>
#include <cuda_runtime.h>

int main()
{
    int deviceCount;
    cudaGetDeviceCount(&deviceCount);

    printf("CUDA capable devices: %d\n\n", deviceCount);

    for (int i = 0; i < deviceCount; i++)
    {
        cudaDeviceProp device;
        cudaGetDeviceProperties(&device, i);

        printf("Device %d\n", i);
        printf("Name: %s\n", device.name);
        printf("Streaming Multiprocessors: %d\n", device.multiProcessorCount);
        printf("Max threads per block: %d\n", device.maxThreadsPerBlock);
        printf("Max thread dimensions: %d %d %d\n",
               device.maxThreadsDim[0],
               device.maxThreadsDim[1],
               device.maxThreadsDim[2]);
        printf("Max grid dimensions: %d %d %d\n",
               device.maxGridSize[0],
               device.maxGridSize[1],
               device.maxGridSize[2]);
        printf("Clock frequency: %.2f GHz\n",
               device.clockRate / 1e6);
    }

    printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
