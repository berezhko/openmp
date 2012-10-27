#include <stdlib.h>
#include <stdio.h>
#include "lapacke.h"

/* Auxiliary routines prototypes */
extern void print_matrix( char* desc, lapack_int m, lapack_int n, double* a, lapack_int lda );
extern void print_int_vector( char* desc, lapack_int n, lapack_int* a );

/* Parameters */
#define N 2000
#define NRHS 1
#define LDA N
#define LDB NRHS

/* Main program */
int main() {
        /* Locals */
        lapack_int n = N, nrhs = NRHS, lda = LDA, ldb = LDB, info;
        /* Local arrays */
        lapack_int ipiv[N];
        int i, j;

        for (i = 0; i < LDA; i++){
            for (j = 0; j < N; j++)
                fscanf(stdin, "%lf", &a[i*N+j]);
            fscanf(stdin, "%lf", &b[i]);
        }

        /* Print Entry Matrix */
        //print_matrix( "Entry Matrix A", n, n, a, lda );
        /* Print Right Rand Side */
        //print_matrix( "Right Rand Side", n, nrhs, b, ldb );
        //printf( "\n" );
        /* Executable statements */
        //printf( "LAPACKE_dgesv (row-major, high-level) Example Program Results\n" );
        /* Solve the equations A*X = B */
        info = LAPACKE_dgesv( LAPACK_ROW_MAJOR, n, nrhs, a, lda, ipiv,
                        b, ldb );
        /* Check for the exact singularity */
        if( info > 0 ) {
                printf( "The diagonal element of the triangular factor of A,\n" );
                printf( "U(%i,%i) is zero, so that A is singular;\n", info, info );
                printf( "the solution could not be computed.\n" );
                exit( 1 );
        }
        /* Print solution */
        //print_matrix( "Solution", n, nrhs, b, ldb );
        /* Print details of LU factorization */
        //print_matrix( "Details of LU factorization", n, n, a, lda );
        /* Print pivot indices */
        //print_int_vector( "Pivot indices", n, ipiv );
        exit( 0 );
} /* End of LAPACKE_dgesv Example */

/* Auxiliary routine: printing a matrix */
void print_matrix( char* desc, lapack_int m, lapack_int n, double* a, lapack_int lda ) {
        lapack_int i, j;
        printf( "\n %s\n", desc );
        for( i = 0; i < m; i++ ) {
                for( j = 0; j < n; j++ ) printf( " %6.2f", a[i*lda+j] );
                printf( "\n" );
        }
}

/* Auxiliary routine: printing a vector of integers */
void print_int_vector( char* desc, lapack_int n, lapack_int* a ) {
        lapack_int j;
        printf( "\n %s\n", desc );
        for( j = 0; j < n; j++ ) printf( " %6i", a[j] );
        printf( "\n" );
}
