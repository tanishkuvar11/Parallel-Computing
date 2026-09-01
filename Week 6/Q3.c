/* Q3) Implement a MPI program to read a 4 X 4 matrix and display the
following output using four processes.

Input matrix:
1 2 3 4
1 2 3 1
1 1 1 1
2 1 2 1

Output matrix:
1 2 3 4
2 4 6 5
3 5 7 6
5 6 9 7 */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int matrix[4][4];
    int row[4];
    int result[4];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size!=4)
    {
        if(rank==0)
            printf("Please run the program with exactly 4 processes.\n");

        MPI_Finalize();
        return 0;
    }

    if(rank==0)
    {
        printf("Enter 16 elements of the matrix:\n");

        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                scanf("%d", &matrix[i][j]);
    }

    MPI_Scatter(matrix, 4, MPI_INT, row, 4, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scan(row, result, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    for(int i=0; i<4; i++)
        matrix[rank][i]=result[i];

    MPI_Gather(result, 4, MPI_INT, matrix, 4, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank==0)
    {
        printf("\nOutput matrix:\n");

        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
                printf("%d ", matrix[i][j]);

            printf("\n");
        }
    }

    MPI_Finalize();

    if(rank==0)
        printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
