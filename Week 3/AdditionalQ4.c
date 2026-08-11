/* Q4) Implement a parallel OpenMP program to estimate the value of pi using
the Monte Carlo (Random Shooting) technique.

Hint:
Randomly generate points inside the square [0,1] x [0,1].
Count the number of points inside the quarter circle.
Compare the execution time for different numbers of threads. */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_POINTS 10000000

int main()
{
    int thread_counts[]={1, 2, 4, 8};

    for(int t=0; t<4; t++)
    {
        int threads=thread_counts[t];
        long long inside=0;

        omp_set_num_threads(threads);

        double start=omp_get_wtime();

        #pragma omp parallel
        {
            unsigned int seed=omp_get_thread_num();

            #pragma omp for reduction(+:inside)
            for(long long i=0; i<NUM_POINTS; i++)
            {
                double x=(double)rand_r(&seed)/RAND_MAX;
                double y=(double)rand_r(&seed)/RAND_MAX;

                if(x*x+y*y<=1.0)
                    inside++;
            }
        }

        double end=omp_get_wtime();

        double pi=4.0*(double)inside/NUM_POINTS;

        printf("Threads: %d\n", threads);
        printf("Points inside circle: %lld\n", inside);
        printf("Estimated Pi: %f\n", pi);
        printf("Execution Time: %f seconds\n\n", end-start);
    }
    
    printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
