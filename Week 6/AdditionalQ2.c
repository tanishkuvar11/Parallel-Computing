/* Q2) Implement a MPI program to read matrix A of size 5 X 5. It produces
a resultant matrix B of size 5 X 5.

Set all the principal diagonal elements of B matrix to 0.

If an element is below the principal diagonal, replace it with the maximum
value of the column in A matrix having the same row number of B.

If an element is above the principal diagonal, replace it with the minimum
value of the column in A matrix having the same row number of B.

Produce the B matrix using 5 processes.

Use only Collective communication routines except broadcast routine. */

#include <stdio.h>
#include <mpi.h>

#define N 5

int main(int argc, char *argv[])
{
    int rank, size;
    int A[N][N];
    int columns[N][N];
    int column[N];
    int B[N][N];
    int row[N];
    int min, max;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size!=N)
    {
        if(rank==0)
            printf("Please run the program with exactly 5 processes.\n");

        MPI_Finalize();
        return 0;
    }

    if(rank==0)
    {
        printf("Enter 25 elements of matrix A:\n");

        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                scanf("%d", &A[i][j]);

        /*
        Store each column of A as a separate block.
        Process 0 receives column 0,
        Process 1 receives column 1, and so on.
        */

        for(int j=0; j<N; j++)
            for(int i=0; i<N; i++)
                columns[j][i]=A[i][j];
    }

    MPI_Scatter(columns, N, MPI_INT, column, N, MPI_INT,
                0, MPI_COMM_WORLD);

    min=column[0];
    max=column[0];

    for(int i=1; i<N; i++)
    {
        if(column[i]<min)
            min=column[i];

        if(column[i]>max)
            max=column[i];
    }

    for(int j=0; j<N; j++)
    {
        if(rank==j)
            row[j]=0;
        else if(rank>j)
            row[j]=max;
        else
            row[j]=min;
    }

    MPI_Gather(row, N, MPI_INT, B, N, MPI_INT,
               0, MPI_COMM_WORLD);

    if(rank==0)
    {
        printf("\nMatrix B:\n");

        for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
                printf("%d ", B[i][j]);

            printf("\n");
        }

        printf("\nTanish Kuvar, 240962540\n");
    }

    MPI_Finalize();

    return 0;
}
