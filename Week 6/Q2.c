/* Q2) Implement a MPI program to read a 3 X 3 matrix. Enter an element to be
searched in the root process. Find the number of occurrences of this
element in the matrix using three processes. */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int matrix[3][3];
    int row[3];
    int search;
    int local_count=0;
    int total_count=0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size!=3)
    {
        if(rank==0)
            printf("Please run the program with exactly 3 processes.\n");

        MPI_Finalize();
        return 0;
    }

    if(rank==0)
    {
        printf("Enter 9 elements of the matrix:\n");

        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                scanf("%d", &matrix[i][j]);

        printf("Enter the element to search: ");
        fflush(stdout);
        scanf("%d", &search);
    }

    MPI_Bcast(&search, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(matrix, 3, MPI_INT, row, 3, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i=0; i<3; i++)
        if(row[i]==search)
            local_count++;

    printf("Process %d: Occurrences in its row = %d\n", rank, local_count);

    MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank==0)
    {
        printf("\nTotal occurrences of %d = %d\n", search, total_count);
        printf("\nTanish Kuvar, 240962540\n");
    }

    MPI_Finalize();

    return 0;
}
