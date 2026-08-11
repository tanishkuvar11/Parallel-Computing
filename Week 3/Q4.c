/* Q4) Write a parallel program using OpenMP to implement the Merge Sort
algorithm.

Analyze the performance by computing:
1. Sequential execution time
2. Parallel execution time
3. Speedup
4. Efficiency

for varying input sizes and thread counts. */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int arr[], int left, int mid, int right)
{
    int i=left;
    int j=mid+1;
    int k=0;

    int size=right-left+1;
    int *temp=(int*)malloc(size*sizeof(int));

    while(i<=mid && j<=right)
    {
        if(arr[i]<=arr[j])
            temp[k++]=arr[i++];
        else
            temp[k++]=arr[j++];
    }

    while(i<=mid)
        temp[k++]=arr[i++];

    while(j<=right)
        temp[k++]=arr[j++];

    for(i=left, k=0; i<=right; i++, k++)
        arr[i]=temp[k];

    free(temp);
}

void mergeSort(int arr[], int left, int right)
{
    if(left<right)
    {
        int mid=(left+right)/2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);

        merge(arr, left, mid, right);
    }
}

void parallelMergeSort(int arr[], int left, int right, int depth)
{
    if(left<right)
    {
        int mid=(left+right)/2;

        if(depth>0)
        {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSort(arr, left, mid, depth-1);

                #pragma omp section
                parallelMergeSort(arr, mid+1, right, depth-1);
            }
        }
        else
        {
            mergeSort(arr, left, mid);
            mergeSort(arr, mid+1, right);
        }

        merge(arr, left, mid, right);
    }
}

int main()
{
    int sizes[]={10000, 50000, 100000};
    int thread_counts[]={2, 8};

    for(int s=0; s<3; s++)
    {
        int N=sizes[s];

        int *original=(int *)malloc(N*sizeof(int));
        int *seq=(int *)malloc(N*sizeof(int));
        int *par=(int *)malloc(N*sizeof(int));

        for(int i=0; i<N; i++)
            original[i]=rand()%100000;

        for(int i=0; i<N; i++)
        {
            seq[i]=original[i];
            par[i]=original[i];
        }

        double start=omp_get_wtime();

        mergeSort(seq, 0, N-1);

        double sequential_time=omp_get_wtime()-start;

        printf("\nInput Size: %d\n", N);
        printf("Sequential Time: %f seconds\n", sequential_time);

        for(int t=0; t<2; t++)
        {
            int threads=thread_counts[t];

            for(int i=0; i<N; i++)
                par[i]=original[i];

            omp_set_num_threads(threads);

            start=omp_get_wtime();

            #pragma omp parallel
            {
                #pragma omp single
                parallelMergeSort(par, 0, N-1, 3);
            }

            double parallel_time=omp_get_wtime()-start;
            double speedup=sequential_time/parallel_time;
            double efficiency=speedup/threads;

            printf("Threads: %d\n", threads);
            printf("Parallel Time: %f seconds\n", parallel_time);
            printf("Speedup: %f\n", speedup);
            printf("Efficiency: %f\n", efficiency);
        }

        free(original);
        free(seq);
        free(par);
    }
    
    printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
