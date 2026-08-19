/* Q7) Implement a MPI program to read N elements of the array in the root
process (process 0) where N is equal to the total number of processes.
The root process sends one value to each of the slaves. Let even ranked
process finds square of the received element and odd ranked process finds
cube of received element. Use Buffered send. */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value, result;
    int *buffer;
    int buffer_size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0)
    {
        int arr[size];

        printf("Enter %d elements:\n", size);

        for(int i=0; i<size; i++)
            scanf("%d", &arr[i]);

        buffer_size=size*(MPI_BSEND_OVERHEAD+sizeof(int));

        buffer=(int *)malloc(buffer_size);

        MPI_Buffer_attach(buffer, buffer_size);

        for(int i=1; i<size; i++)
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);

        value=arr[0];

        if(rank%2==0)
            result=value*value;
        else
            result=value*value*value;

        printf("Process %d: Value = %d, Result = %d\n",
               rank, value, result);

        MPI_Buffer_detach(&buffer, &buffer_size);

        free(buffer);
    }
    else
    {
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if(rank%2==0)
            result=value*value;
        else
            result=value*value*value;

        printf("Process %d: Value = %d, Result = %d\n",
               rank, value, result);
    }

    MPI_Finalize();
    
    if(rank==0)
        printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
