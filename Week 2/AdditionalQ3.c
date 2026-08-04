/* 3. Implement an OpenMP program to reverse the digits of every element in the given array */

#include<stdio.h>
#include<omp.h>

int main()
{
    int a[9]={18, 523, 301, 1234, 2, 14, 108, 150, 1928};

    printf("Original array:\n");
    for(int i=0; i<9; i++)
        printf("%d ", a[i]);

    #pragma omp parallel for
    for(int i=0; i<9; i++)
    {
        int num=a[i], rev=0;

        while(num>0)
        {
            rev=rev*10+num%10;
            num/=10;
        }

        a[i]=rev;
    }

    printf("\nReversed array:\n");
    for(int i=0; i<9; i++)
        printf("%d ", a[i]);

    printf("\nTanish Kuvar, 240962540\n");
}
