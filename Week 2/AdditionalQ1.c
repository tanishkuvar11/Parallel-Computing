/* 1. Implement an OpenMP program to calculate pow(i, x), where i is an integer entered by the user and x is the Thread ID */

#include<stdio.h>
#include<math.h>
#include<omp.h>

int main()
{
    int i;

    printf("Enter i: ");
    scanf("%d", &i);

    #pragma omp parallel
    {
        int x=omp_get_thread_num();
        printf("Thread %d: %d^%d=%.0f\n", x, i, x, pow(i, x));
    }

    printf("\nTanish Kuvar, 240962540\n");
}
