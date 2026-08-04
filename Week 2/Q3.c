/* Implement an OpenMP program that reads a matrix of size M × N and produces:
	Matrix B, where all non-border elements are replaced by their 1's complement (binary 1's complement). Border elements remain unchanged.
	Matrix D, where each non-border element contains the decimal equivalent of the 1's complement of the corresponding element in Matrix A. Border elements remain unchanged. */

#include<stdio.h>
#include<omp.h>

int main()
{
    int m, n;

    printf("Enter rows and columns: ");
    scanf("%d %d",&m,&n);

    int A[m][n], B[m][n], D[m][n];

    printf("Enter matrix:\n");
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &A[i][j]);

    #pragma omp parallel for collapse(2)
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==0||i==m-1||j==0||j==n-1)
            {
                B[i][j]=A[i][j];
                D[i][j]=A[i][j];
            }
            
            else
            {
                int x=A[i][j];
                int bits=0,temp=x;

                while(temp)
                {
                    bits++;
                    temp/=2;
                }

                if(bits==0)
                    bits=1;

                int comp=0, dec=0, p=1;

                for(int k=0;k<bits;k++)
                {
                    int bit=x%2;
                    bit=1-bit;

                    comp+=bit*p;
                    dec+=bit*(1<<k);

                    p*=10;
                    x/=2;
                }

                B[i][j]=comp;
                D[i][j]=dec;
            }
        }
    }

    printf("\nB:\n");
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
            printf("%d ",B[i][j]);
        printf("\n");
    }

    printf("\nD:\n");
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
            printf("%d ",D[i][j]);
        printf("\n");
    }

    printf("\nTanish Kuvar, 240962540\n");
}
