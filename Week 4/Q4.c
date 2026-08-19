/* Q4) Implement a MPI program using synchronous send. The sender process
sends a word to the receiver. The second process receives the word,
toggles each letter of the word and sends it back to the first process.
Both processes use synchronous send operations. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    char word[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank==0)
    {
        strcpy(word, "HELLO");

        printf("Process 0: Sending word = %s\n", word);

        MPI_Ssend(word, strlen(word)+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(word, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 0: Received word = %s\n", word);
    }
    else if(rank==1)
    {
        MPI_Recv(word, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for(int i=0; word[i]!='\0'; i++)
        {
            if(isupper(word[i]))
                word[i]=tolower(word[i]);
            else if(islower(word[i]))
                word[i]=toupper(word[i]);
        }

        printf("Process 1: Toggled word = %s\n", word);

        MPI_Ssend(word, strlen(word)+1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }
    
	MPI_Finalize();

    if(rank==0)
        printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
