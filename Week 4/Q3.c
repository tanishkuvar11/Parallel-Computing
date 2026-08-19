/* Q3) Implement a program in MPI where even ranked process prints factorial
of the rank and odd ranked process prints rank's Fibonacci number. */

#include <stdio.h>
#include <mpi.h>

int factorial(int n)
{
    if(n==0)
		return 1;
		
	return n*factorial(n-1);
}

int fibonacci(int n)
{
    if(n==0)
		return 0;
		
	if(n==1)
		return 1;
		
	return fibonacci(n-1)+fibonacci(n-2);
}

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank%2==0)
        printf("Process %d: Factorial = %lld\n", rank, factorial(rank));
    else
        printf("Process %d: Fibonacci = %lld\n", rank, fibonacci(rank));

    MPI_Finalize();
    
    if(rank==0)
        printf("\nTanish Kuvar, 240962540\n");

    return 0;
}
