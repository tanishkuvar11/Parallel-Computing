#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

int is_vowel(char ch)
{
    ch = tolower(ch);

    return (ch == 'a' ||
            ch == 'e' ||
            ch == 'i' ||
            ch == 'o' ||
            ch == 'u');
}

int main(int argc, char *argv[])
{
    int rank, size;
    int length;
    int local_count = 0;
    int total_count = 0;

    char *string = NULL;
    char *local_string;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter a string: ");

        string = (char *)malloc(1000 * sizeof(char));

        scanf(" %[^\n]", string);

        length = strlen(string);

        if (length % size != 0)
        {
            printf("String length must be divisible by number of processes.\n");

            free(string);
            MPI_Finalize();
            return 0;
        }
    }

    /* Send string length to all processes */
    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_length = length / size;

    local_string = (char *)malloc(local_length * sizeof(char));

    /* Divide string equally */
    MPI_Scatter(string, local_length, MPI_CHAR,
                local_string, local_length, MPI_CHAR,
                0, MPI_COMM_WORLD);

    for (int i = 0; i < local_length; i++)
    {
        if (!is_vowel(local_string[i]))
            local_count++;
    }

    printf("Process %d: Non-vowels = %d\n",
           rank, local_count);

    /* Add all counts at root */
    MPI_Reduce(&local_count, &total_count, 1, MPI_INT,
               MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nTotal number of non-vowels = %d\n",
               total_count);
               
         printf("\nSiddhant Bhardwaj\n");


        free(string);
    }

    free(local_string);

    MPI_Finalize();

    return 0;
}
