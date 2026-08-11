/* Q3) Implement an OpenMP program using C to determine the number of prime
numbers within a given range (1 to N) using the parallel for directive.
Since checking whether a number is prime requires a varying amount of
computation depending on the number being tested, this problem exhibits
an imbalanced workload across loop iterations.

Execute the program separately using the following OpenMP scheduling policies:
1. schedule(static)
2. schedule(dynamic)
3. schedule(guided)

For each scheduling policy:
- Record the thread ID responsible for processing each number.
- Measure the execution time using omp_get_wtime().
- Observe how loop iterations are distributed among the threads.
- Compare the load balancing and execution time obtained with each
  scheduling policy. */

#include <stdio.h>
#include <omp.h>

#define N 10

int main()
{
    int count;
    double start, end;

    // 1. static
    count=0;

    start=omp_get_wtime();

    #pragma omp parallel for schedule(static) reduction(+:count)
    for(int i=1; i<=N; i++)
    {
        int prime=1;

        if(i<2)
            prime=0;

        else
        {
            for(int j=2; j*j<=i; j++)
            {
                if(i%j==0)
                {
                    prime=0;
                    break;
                }
            }
        }

        if(prime)
            count++;

        printf("Static: Number %d processed by Thread %d\n",
               i, omp_get_thread_num());
    }

    end=omp_get_wtime();

    printf("Static: Prime Count = %d\n", count);
    printf("Static: Execution Time = %f seconds\n\n", end-start);


    // 2. Dynamic
    count=0;

    start=omp_get_wtime();

    #pragma omp parallel for schedule(dynamic) reduction(+:count)
    for(int i=1; i<=N; i++)
    {
        int prime=1;

        if(i<2)
            prime=0;
            
        else
        {
            for(int j=2; j*j<=i; j++)
            {
                if(i%j==0)
                {
                    prime=0;
                    break;
                }
            }
        }

        if(prime)
            count++;

        printf("Dynamic: Number %d processed by Thread %d\n",
               i, omp_get_thread_num());
    }

    end=omp_get_wtime();

    printf("Dynamic: Prime Count = %d\n", count);
    printf("Dynamic: Execution Time = %f seconds\n\n", end-start);


    // 3. Guided
    count=0;

    start=omp_get_wtime();

    #pragma omp parallel for schedule(guided) reduction(+:count)
    for(int i=1; i<=N; i++)
    {
        int prime=1;

        if(i<2)
            prime=0;
            
        else
        {
            for(int j=2; j*j<=i; j++)
            {
                if(i%j==0)
                {
                    prime=0;
                    break;
                }
            }
        }

        if(prime)
            count++;

        printf("Guided: Number %d processed by Thread %d\n",
               i, omp_get_thread_num());
    }

    end=omp_get_wtime();

    printf("Guided: Prime Count = %d\n", count);
    printf("Guided: Execution Time = %f seconds\n", end-start);
    
    printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
