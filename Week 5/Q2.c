#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int M;

    int *array = NULL;
    int *local_array;

    int local_sum = 0;
    int total_sum = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter M (number of elements per process): ");
        scanf("%d", &M);

        array = (int *)malloc(M * size * sizeof(int));

        printf("Enter %d elements:\n", M * size);

        for (int i = 0; i < M * size; i++)
            scanf("%d", &array[i]);
    }

    /* Broadcast M to all processes */
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_array = (int *)malloc(M * sizeof(int));

    /* Distribute M elements to each process */
    MPI_Scatter(array, M, MPI_INT,
                local_array, M, MPI_INT,
                0, MPI_COMM_WORLD);

    for (int i = 0; i < M; i++)
        local_sum += local_array[i];

    printf("Process %d: Local average = %.2f\n",
           rank, (float)local_sum / M);

    /* Calculate total sum */
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT,
               MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        double average = (double)total_sum / (M * size);

        printf("\nTotal average = %.2f\n", average);


        free(array);
    }

    free(local_array);

    MPI_Finalize();

    return 0;
}
