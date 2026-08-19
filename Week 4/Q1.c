/* Q1) Implement a simple MPI program to find out pow(x, rank) for all the
processes where 'x' is the integer constant and 'rank' is the rank of
the process. */

#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int x=2;
    int result=1;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for(int i=0; i<rank; i++)
        result*=x;

    printf("Process %d: %d^%d = %d\n", rank, x, rank, result);

    MPI_Finalize();
    
    if(rank==0)
		printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
