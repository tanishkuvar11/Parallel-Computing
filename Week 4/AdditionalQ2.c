/* Additional Q2) Implement a MPI program to read N elements of an array in
the master process. Let N processes including the master process check
the array values are prime or not. */

#include <stdio.h>
#include <mpi.h>

int isPrime(int n)
{
    if(n<2)
        return 0;

    for(int i=2; i*i<=n; i++)
        if(n%i==0)
            return 0;

    return 1;
}

int main(int argc, char *argv[])
{
    int rank, size;
    int value;
    int arr[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0)
    {
        printf("Enter %d elements:\n", size);

        for(int i=0; i<size; i++)
            scanf("%d", &arr[i]);

        for(int i=1; i<size; i++)
            MPI_Send(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);

        value=arr[0];
    }
    else
    {
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    if(isPrime(value))
        printf("Process %d: %d is Prime\n", rank, value);
    else
        printf("Process %d: %d is Not Prime\n", rank, value);

    MPI_Finalize();

    if(rank==0)
        printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
