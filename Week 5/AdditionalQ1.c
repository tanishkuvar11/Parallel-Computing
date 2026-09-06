#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

long long cube(long long x)
{
    return x * x * x;
}

int main(int argc, char *argv[])
{
    int rank, size;
    int M;

    int *array = NULL;
    int *local_array;

    long long local_result = 0;
    long long *results = NULL;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter M: ");
        scanf("%d", &M);

        array = (int *)malloc(M * size * sizeof(int));

        printf("Enter %d elements:\n", M * size);

        for (int i = 0; i < M * size; i++)
            scanf("%d", &array[i]);
    }

    /* Broadcast M */
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_array = (int *)malloc(M * sizeof(int));

    /* Distribute M elements to each process */
    MPI_Scatter(array, M, MPI_INT,
                local_array, M, MPI_INT,
                0, MPI_COMM_WORLD);

    /*
       Even process:
       Calculate sum.

       Odd process:
       Calculate sum of cubes.
    */
    if (rank % 2 == 0)
    {
        for (int i = 0; i < M; i++)
            local_result += local_array[i];

        printf("Process %d: Sum = %lld\n",
               rank, local_result);
    }
    else
    {
        for (int i = 0; i < M; i++)
            local_result += cube(local_array[i]);

        printf("Process %d: Cube sum = %lld\n",
               rank, local_result);
    }

    if (rank == 0)
        results = (long long *)malloc(size * sizeof(long long));

    /* Gather results at root */
    MPI_Gather(&local_result, 1, MPI_LONG_LONG,
               results, 1, MPI_LONG_LONG,
               0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nResults:\n");

        for (int i = 0; i < size; i++)
        {
            if (i % 2 == 0)
                printf("Process %d - Sum = %lld\n",
                       i, results[i]);
            else
                printf("Process %d - Cube Sum = %lld\n",
                       i, results[i]);
        }



        free(array);
        free(results);
    }

    free(local_array);

    MPI_Finalize();

    return 0;
}
