/* Q1) Implement a MPI program using N processes to find:

1! + 2! + 3! + ... + N!

Use MPI_Scan().
Also, handle different errors using MPI error handling routines. */

#include <stdio.h>
#include <mpi.h>

void checkError(int error_code, char message[])
{
    if(error_code!=MPI_SUCCESS)
    {
        char error_string[MPI_MAX_ERROR_STRING];
        int length;

        MPI_Error_string(error_code, error_string, &length);

        printf("%s: %s\n", message, error_string);

        MPI_Abort(MPI_COMM_WORLD, error_code);
    }
}

long long factorial(int n)
{
    long long fact=1;

    for(int i=1; i<=n; i++)
        fact*=i;

    return fact;
}

int main(int argc, char *argv[])
{
    int rank, size;
    int error_code;
    long long fact, sum;

    error_code=MPI_Init(&argc, &argv);

    if(error_code!=MPI_SUCCESS)
    {
        printf("Error initializing MPI.\n");
        return 1;
    }

    error_code=MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    checkError(error_code, "Error setting error handler");

    error_code=MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    checkError(error_code, "Error getting process rank");

    error_code=MPI_Comm_size(MPI_COMM_WORLD, &size);
    checkError(error_code, "Error getting number of processes");

    fact=factorial(rank+1);

    printf("Process %d: %d! = %lld\n", rank, rank+1, fact);

    error_code=MPI_Scan(&fact, &sum, 1, MPI_LONG_LONG,
                        MPI_SUM, MPI_COMM_WORLD);
    checkError(error_code, "Error performing MPI_Scan");

    printf("Process %d: Partial sum = %lld\n", rank, sum);

    if(rank==size-1)
        printf("\nFinal Sum = %lld\n", sum);

    MPI_Finalize();

    if(rank==0)
        printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
