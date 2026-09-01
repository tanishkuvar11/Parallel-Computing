#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int length;

    char *S1 = NULL;
    char *S2 = NULL;
    char *result = NULL;

    char *local_S1;
    char *local_S2;
    char *local_result;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        S1 = (char *)malloc(1000 * sizeof(char));
        S2 = (char *)malloc(1000 * sizeof(char));

        printf("Enter string S1: ");
        scanf("%s", S1);

        printf("Enter string S2: ");
        scanf("%s", S2);

        length = strlen(S1);

        if (strlen(S2) != length)
        {
            printf("Both strings must have the same length.\n");

            free(S1);
            free(S2);

            MPI_Finalize();
            return 0;
        }

        if (length % size != 0)
        {
            printf("String length must be divisible by number of processes.\n");

            free(S1);
            free(S2);

            MPI_Finalize();
            return 0;
        }
    }

    /* Send length to all processes */
    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_length = length / size;

    local_S1 = (char *)malloc(local_length * sizeof(char));
    local_S2 = (char *)malloc(local_length * sizeof(char));

    local_result =
        (char *)malloc(2 * local_length * sizeof(char));

    /* Distribute strings */
    MPI_Scatter(S1, local_length, MPI_CHAR,
                local_S1, local_length, MPI_CHAR,
                0, MPI_COMM_WORLD);

    MPI_Scatter(S2, local_length, MPI_CHAR,
                local_S2, local_length, MPI_CHAR,
                0, MPI_COMM_WORLD);

    /* Interleave local strings */
    for (int i = 0; i < local_length; i++)
    {
        local_result[2 * i] = local_S1[i];
        local_result[2 * i + 1] = local_S2[i];
    }

    result = (char *)malloc(2 * length * sizeof(char) + 1);

    /* Gather results */
    MPI_Gather(local_result, 2 * local_length, MPI_CHAR,
               result, 2 * local_length, MPI_CHAR,
               0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        result[2 * length] = '\0';

        printf("\nResultant string = %s\n", result);
		printf("\nSiddhant Bhardwaj\n");

        free(S1);
        free(S2);
        free(result);
    }

    free(local_S1);
    free(local_S2);
    free(local_result);

    MPI_Finalize();

    return 0;
}
