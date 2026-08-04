/* 4. Implement an OpenMP program to generate prime numbers within a user-specified interval using the parallel for directive. */

#include<stdio.h>
#include<omp.h>

int main()
{
    int l, r;

    printf("Enter lower and upper limits: ");
    scanf("%d%d", &l, &r);

    printf("Prime numbers:\n");

    #pragma omp parallel for
    for(int i=l; i<=r; i++)
    {
        if(i<2)
            continue;

        int prime=1;

        for(int j=2; j*j<=i; j++)
        {
            if(i%j==0)
            {
                prime=0;
                break;
            }
        }

        if(prime)
            printf("%d ", i);
    }

    printf("\nTanish Kuvar, 240962540\n");
}
