/* Additional Q1) Implement a program in MPI to reverse the digits of an
   integer array of size 9 with 9 processes */

#include <stdio.h>
#include <mpi.h>

int reverse(int n)
{
    int rev=0;

    while(n>0)
    {
        rev=rev*10+n%10;
        n/=10;
    }

    return rev;
}

int main(int argc, char *argv[])
{
    int rank, size;
    int arr[9]={18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int result;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size!=9)
    {
        if(rank==0)
            printf("Please run the program with 9 processes.\n");

        MPI_Finalize();
        return 0;
    }

    result=reverse(arr[rank]);

    printf("Process %d: %d -> %d\n", rank, arr[rank], result);

    MPI_Finalize();
    
    if(rank==0)
        printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
