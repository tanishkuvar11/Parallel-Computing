#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

long long factorial(int n)
{
    long long fact = 1;

    for (int i = 1; i <= n; i++)
        fact *= i;

    return fact;
}

int main(int argc, char *argv[])
{
    int rank, size;
    int value;
    long long fact;
    long long total = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        int *numbers = (int *)malloc(size * sizeof(int));

        printf("Enter %d numbers:\n", size);

        for (int i = 0; i < size; i++)
            scanf("%d", &numbers[i]);

        /* Send one number to each process */
        for (int i = 0; i < size; i++)
        {
            if (i == 0)
                value = numbers[i];
            else
                MPI_Send(&numbers[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        free(numbers);
    }
    else
    {
        MPI_Recv(&value, 1, MPI_INT, 0, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    fact = factorial(value);

    printf("Process %d: %d! = %lld\n", rank, value, fact);

    /* Gather factorials at root */
    if (rank == 0)
    {
        total += fact;

        for (int i = 1; i < size; i++)
        {
            long long received;

            MPI_Recv(&received, 1, MPI_LONG_LONG,
                     i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            total += received;
        }

        printf("\nSum of factorials = %lld\n", total);
    }
    else
    {
        MPI_Send(&fact, 1, MPI_LONG_LONG,
                 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();



    return 0;
}
