/* Q4) Implement parallel odd even transposition sort using MPI.

The root process reads N elements, where N is equal to the number of
processes. Each process receives one element and the array is sorted
using parallel odd even transposition sort. */

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value, received;
    int *arr;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0)
    {
        arr=(int *)malloc(size*sizeof(int));

        printf("Enter %d elements:\n", size);

        for(int i=0; i<size; i++)
            scanf("%d", &arr[i]);
    }

    MPI_Scatter(arr, 1, MPI_INT, &value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for(int phase=0; phase<size; phase++)
    {
        int partner;

        if(phase%2==0)
        {
            if(rank%2==0)
                partner=rank+1;
            else
                partner=rank-1;
        }
        else
        {
            if(rank%2==0)
                partner=rank-1;
            else
                partner=rank+1;
        }

        if(partner>=0 && partner<size)
        {
            MPI_Sendrecv(&value, 1, MPI_INT, partner, 0,
                         &received, 1, MPI_INT, partner, 0,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if(rank<partner)
            {
                if(received<value)
                    value=received;
            }
            else
            {
                if(received>value)
                    value=received;
            }
        }
    }

    MPI_Gather(&value, 1, MPI_INT, arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank==0)
    {
        printf("\nSorted array:\n");

        for(int i=0; i<size; i++)
            printf("%d ", arr[i]);

        printf("\n");

        printf("\nTanish Kuvar, 240962540\n");

        free(arr);
    }

    MPI_Finalize();

    return 0;
}
