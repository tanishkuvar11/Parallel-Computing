#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void selection_sort(int arr[], int n)
{
    int i, j, min_index, temp;

    for (i = 0; i < n - 1; i++)
    {
        min_index = i;

        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_index])
                min_index = j;
        }

        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

void merge(int arr1[], int n1, int arr2[], int n2, int result[])
{
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2)
    {
        if (arr1[i] <= arr2[j])
            result[k++] = arr1[i++];
        else
            result[k++] = arr2[j++];
    }

    while (i < n1)
        result[k++] = arr1[i++];

    while (j < n2)
        result[k++] = arr2[j++];
}

int main(int argc, char *argv[])
{
    int rank, size;
    int n;

    int *array = NULL;
    int *local_array = NULL;

    int local_n;
    int *sendcounts = NULL;
    int *displacements = NULL;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter number of elements: ");
        scanf("%d", &n);

        array = (int *)malloc(n * sizeof(int));

        printf("Enter %d elements:\n", n);

        for (int i = 0; i < n; i++)
            scanf("%d", &array[i]);
    }

    /* Broadcast array size */
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /*
       Calculate how many elements each process gets.
       MPI_Scatterv allows unequal sizes.
    */
    sendcounts = (int *)malloc(size * sizeof(int));
    displacements = (int *)malloc(size * sizeof(int));

    int base = n / size;
    int remainder = n % size;

    for (int i = 0; i < size; i++)
    {
        sendcounts[i] = base;

        if (i < remainder)
            sendcounts[i]++;
    }

    displacements[0] = 0;

    for (int i = 1; i < size; i++)
        displacements[i] =
            displacements[i - 1] + sendcounts[i - 1];

    local_n = sendcounts[rank];

    local_array = (int *)malloc(local_n * sizeof(int));

    /* Distribute array */
    MPI_Scatterv(array, sendcounts, displacements,
                 MPI_INT, local_array, local_n,
                 MPI_INT, 0, MPI_COMM_WORLD);

    /* Each process performs selection sort */
    selection_sort(local_array, local_n);

    printf("Process %d sorted its subarray: ", rank);

    for (int i = 0; i < local_n; i++)
        printf("%d ", local_array[i]);

    printf("\n");

    /*
       Parallel merging.

       At each step:
       - process 1 sends to process 0
       - process 3 sends to process 2
       - then process 2 sends to process 0
       - etc.
    */

    int step = 1;

    while (step < size)
    {
        if (rank % (2 * step) == 0)
        {
            int source = rank + step;

            if (source < size)
            {
                int received_n;

                MPI_Recv(&received_n, 1, MPI_INT,
                         source, 0, MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE);

                int *received_array =
                    (int *)malloc(received_n * sizeof(int));

                MPI_Recv(received_array, received_n, MPI_INT,
                         source, 1, MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE);

                int *merged =
                    (int *)malloc((local_n + received_n) *
                                  sizeof(int));

                merge(local_array, local_n,
                      received_array, received_n,
                      merged);

                free(local_array);
                free(received_array);

                local_array = merged;
                local_n += received_n;
            }
        }
        else
        {
            int destination = rank - step;

            MPI_Send(&local_n, 1, MPI_INT,
                     destination, 0, MPI_COMM_WORLD);

            MPI_Send(local_array, local_n, MPI_INT,
                     destination, 1, MPI_COMM_WORLD);

            free(local_array);

            break;
        }

        step *= 2;
    }

    /* Process 0 has the final sorted array */
    if (rank == 0)
    {
        printf("\nFinal sorted array:\n");

        for (int i = 0; i < n; i++)
            printf("%d ", local_array[i]);

        printf("\n");


        free(array);
        free(local_array);
    }

    free(sendcounts);
    free(displacements);

    MPI_Finalize();

    return 0;
}
