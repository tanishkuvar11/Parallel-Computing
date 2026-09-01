#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int N;

    int *array = NULL;
    int *local_array;

    int local_even = 0;
    int local_odd = 0;

    int total_even = 0;
    int total_odd = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter N: ");
        scanf("%d", &N);

        if (N % size != 0)
        {
            printf("N must be divisible by number of processes.\n");

            MPI_Finalize();
            return 0;
        }

        array = (int *)malloc(N * sizeof(int));

        printf("Enter %d elements:\n", N);

        for (int i = 0; i < N; i++)
            scanf("%d", &array[i]);
    }

    /* Send N to all processes */
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_N = N / size;

    local_array = (int *)malloc(local_N * sizeof(int));

    /* Distribute array */
    MPI_Scatter(array, local_N, MPI_INT,
                local_array, local_N, MPI_INT,
                0, MPI_COMM_WORLD);

    /* Replace values */
    for (int i = 0; i < local_N; i++)
    {
        if (local_array[i] % 2 == 0)
        {
            local_array[i] = 0;
            local_even++;
        }
        else
        {
            local_array[i] = 1;
            local_odd++;
        }
    }

    /* Collect transformed array */
    MPI_Gather(local_array, local_N, MPI_INT,
               array, local_N, MPI_INT,
               0, MPI_COMM_WORLD);

    /* Calculate total even and odd counts */
    MPI_Reduce(&local_even, &total_even, 1, MPI_INT,
               MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Reduce(&local_odd, &total_odd, 1, MPI_INT,
               MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nResultant Array (A): ");

        for (int i = 0; i < N; i++)
            printf("%d ", array[i]);

        printf("\n");

        printf("Even Count = %d\n", total_even);
        printf("Odd Count  = %d\n", total_odd);
        printf("\nSiddhant Bhardwaj\n");


        free(array);
    }

    free(local_array);

    MPI_Finalize();

    return 0;
}
