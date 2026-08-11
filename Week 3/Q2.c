/* Q2) Implement a C program using OpenMP to process an integer array in parallel
and demonstrate the use of the following synchronization constructs:
1. critical
2. atomic
3. reduction
4. master

The program should perform the following tasks:
1. The master thread should initialize the array and display the total number
   of threads participating in the computation.
2. Use the reduction clause to compute the sum of all array elements in parallel.
3. Use the atomic construct to count the number of even elements in the array.
4. Use the critical construct to allow each thread to safely display its thread
   ID and the partial sum of the array elements processed by that thread.
5. After all threads complete execution, the master thread should display the
   final sum of the array elements and the total count of even numbers. */

#include <stdio.h>
#include <omp.h>

#define N 10

int main()
{
    int arr[N];
    int sum=0;
    int even_count=0;

    #pragma omp parallel
    {
        int thread_sum=0;

        #pragma omp master
        {
            for (int i=0; i<N; i++)
                arr[i]=i+1;

            printf("Number of threads: %d\n", omp_get_num_threads());
        }

        #pragma omp barrier

        #pragma omp for reduction(+:sum)
        for (int i=0; i<N; i++)
        {
            sum+=arr[i];
            thread_sum+=arr[i];

            if (arr[i]%2==0)
            {
                #pragma omp atomic
                even_count++;
            }
        }

        #pragma omp critical
        {
            printf("Thread %d: Partial Sum = %d\n",
                   omp_get_thread_num(), thread_sum);
        }

        #pragma omp barrier

        #pragma omp master
        {
            printf("Final Sum: %d\n", sum);
            printf("Even Count: %d\n", even_count);
        }
    }
    
    printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
