/* Additional Q2) Implement a parallel OpenMP program to generate the histogram of a given
array. Compare the execution time of the sequential and parallel
implementations. */

#include <stdio.h>
#include <omp.h>

#define N 20
#define MAX_VALUE 10

int main()
{
    int arr[N]={1, 2, 3, 4, 5, 2, 3, 1, 5, 4,
                2, 6, 7, 3, 8, 5, 9, 1, 6, 2};

    int hist_seq[MAX_VALUE+1]={0};
    int hist_par[MAX_VALUE+1]={0};

    double start, end;
    double seq_time, par_time;

    // Sequential
    start=omp_get_wtime();

    for(int i=0; i<N; i++)
        hist_seq[arr[i]]++;

    end=omp_get_wtime();

    seq_time=end-start;

    // Parallel
    start=omp_get_wtime();

    #pragma omp parallel for
    for(int i=0; i<N; i++)
    {
        #pragma omp atomic
        hist_par[arr[i]]++;
    }

    end=omp_get_wtime();

    par_time=end-start;

    printf("Sequential Histogram:\n");

    for(int i=0; i<=MAX_VALUE; i++)
        if(hist_seq[i]>0)
            printf("%d: %d\n", i, hist_seq[i]);

    printf("\nParallel Histogram:\n");

    for(int i=0; i<=MAX_VALUE; i++)
        if(hist_par[i]>0)
            printf("%d: %d\n", i, hist_par[i]);

    printf("\nSequential Time: %f seconds\n", seq_time);
    printf("Parallel Time: %f seconds\n", par_time);
    
    printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
