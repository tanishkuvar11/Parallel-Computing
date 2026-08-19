/* Q6) Implement a MPI program to read an integer value in the root process.
Root process sends this value to Process 1, Process 1 sends this value to
Process 2 and so on. Last process sends the value back to root process.
When sending the value each process will first increment the received
value by one. Implement the program using point to point communication
routines. */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0)
    {
        scanf("%d", &value);

        printf("Process %d: Initial value = %d\n", rank, value);

        if(size==1)
            value++;
        else
        {
            MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&value, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("Process %d: Final value = %d\n", rank, value);
    }
    else
    {
        MPI_Recv(&value, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        value++;

        printf("Process %d: Incremented value = %d\n", rank, value);

        if(rank==size-1)
            MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        else
            MPI_Send(&value, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    if(rank==0)
        printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
