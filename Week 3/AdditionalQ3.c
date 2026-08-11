/* Q3) Implement an OpenMP program to compute the factorial of N using:
1. Critical Section
2. Atomic
3. Reduction
4. Master
5. Locks

Compare the execution time of each synchronization construct. */

#include <stdio.h>
#include <omp.h>

#define N 10

int main()
{
    long long factorial;
    double start, end;

    // 1. Critical
    factorial=1;

    start=omp_get_wtime();

    #pragma omp parallel for
    for(int i=1; i<=N; i++)
    {
        #pragma omp critical
        {
            factorial*=i;
        }
    }

    end=omp_get_wtime();

    printf("Critical: %lld\n", factorial);
    printf("Time: %f seconds\n\n", end-start);


    // 2. Atomic
    factorial=1;

    start=omp_get_wtime();

    #pragma omp parallel for
    for(int i=1; i<=N; i++)
    {
        #pragma omp atomic
        factorial*=i;
    }

    end=omp_get_wtime();

    printf("Atomic: %lld\n", factorial);
    printf("Time: %f seconds\n\n", end-start);


    // 3. Reduction
    factorial=1;

    start=omp_get_wtime();

    #pragma omp parallel for reduction(*:factorial)
    for(int i=1; i<=N; i++)
        factorial*=i;

    end=omp_get_wtime();

    printf("Reduction: %lld\n", factorial);
    printf("Time: %f seconds\n\n", end-start);


    // 4. Master
    factorial=1;

    start=omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp master
        {
            for(int i=1; i<=N; i++)
                factorial*=i;
        }
    }

    end=omp_get_wtime();

    printf("Master: %lld\n", factorial);
    printf("Time: %f seconds\n\n", end-start);


    // 5. Lock
    factorial=1;

    omp_lock_t lock;
    omp_init_lock(&lock);

    start=omp_get_wtime();

    #pragma omp parallel for
    for(int i=1; i<=N; i++)
    {
        omp_set_lock(&lock);
        factorial*=i;
        omp_unset_lock(&lock);
    }

    end=omp_get_wtime();

    printf("Lock: %lld\n", factorial);
    printf("Time: %f seconds\n", end-start);

    omp_destroy_lock(&lock);
    
    printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
