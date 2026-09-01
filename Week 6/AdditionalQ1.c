/* Q1) Implement a MPI program to read a word of length N. Using N processes
including the root get output word with the pattern as shown in example.
Display the resultant output word in the root.

Example:
Input: PCAP
Output: PCCAAAPPPP */

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char word[100];
    char ch;
    char local[100];
    char output[10000];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0)
    {
        printf("Enter a word of length %d: ", size);
        fflush(stdout);

        scanf("%s", word);

        if(strlen(word)!=size)
        {
            printf("Word length must be equal to number of processes.\n");

            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    MPI_Scatter(word, 1, MPI_CHAR, &ch, 1, MPI_CHAR,
                0, MPI_COMM_WORLD);

    for(int i=0; i<rank+1; i++)
        local[i]=ch;

    int recvcounts[size];
    int displs[size];

    if(rank==0)
    {
        displs[0]=0;

        for(int i=0; i<size; i++)
        {
            recvcounts[i]=i+1;

            if(i>0)
                displs[i]=displs[i-1]+recvcounts[i-1];
        }
    }

    MPI_Gatherv(local, rank+1, MPI_CHAR,
                output, recvcounts, displs, MPI_CHAR,
                0, MPI_COMM_WORLD);

    if(rank==0)
    {
        int total=size*(size+1)/2;

        output[total]='\0';

        printf("Output: %s\n", output);
        printf("\nTanish Kuvar, 240962540\n");
    }

    MPI_Finalize();

    return 0;
}
