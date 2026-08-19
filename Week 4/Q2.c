/* Q2) Implement a program in MPI to toggle the character of a given string
indexed by the rank of the process */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char str[]="HELLO";

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank<strlen(str))
    {
        str[rank]=tolower(str[rank]);

        printf("Process %d: %c\n", rank, str[rank]);
    }

    MPI_Finalize();
    
    if(rank==0)
		printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
