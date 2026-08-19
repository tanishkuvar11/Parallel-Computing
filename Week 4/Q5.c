/* Q5) Implement a MPI program where the master process (process 0) sends a
number to each of the slaves and the slave processes receive the number
and print it. Use standard send. */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int number=10;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0)
    {
        for(int i=1; i<size; i++)
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received number: %d\n", rank, number);
    }
    
    MPI_Finalize();

    if(rank==0)
        printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
