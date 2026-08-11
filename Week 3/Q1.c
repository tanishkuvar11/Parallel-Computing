/* Q1) Implement an OpenMP program to compute the sum of the first N natural
numbers in parallel. Using the same program, demonstrate the effect of
the following OpenMP data-sharing clauses:
1. shared
2. private
3. firstprivate
4. lastprivate */

#include <stdio.h>
#include <omp.h>

#define N 10

int main()
{
    int sum;

    // 1. shared
    sum=0;

    #pragma omp parallel for shared(sum)
    for (int i=1; i<=N; i++)
        sum+=i;

    printf("Shared: %d\n", sum);

    // 2. private
    sum=0;

    #pragma omp parallel for private(sum)
    for (int i=1; i<=N; i++)
        sum+=i;

    printf("Private: %d\n", sum);

    // 3. firstprivate
    sum=0;

    #pragma omp parallel for firstprivate(sum)
    for (int i=1; i<=N; i++)
        sum+=i;

    printf("Firstprivate: %d\n", sum);

    // 4. lastprivate
    sum=0;

    #pragma omp parallel for lastprivate(sum)
    for (int i=1; i<=N; i++)
        sum+=i;

    printf("Lastprivate: %d\n", sum);
    
    printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
