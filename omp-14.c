#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <omp.h>

#define SIZE 100000000

int main(){
    int i;
    int p, size;
    double *M, *N;
    double start_time, end_time, tick;

    M = malloc(sizeof(double)*SIZE);
    N = malloc(sizeof(double)*SIZE);

    tick = omp_get_wtick();

    bzero(N, SIZE);
    bzero(M, SIZE);

    start_time = omp_get_wtime();
    end_time = omp_get_wtime();
    printf("Реальное время на замер времени null %.12lf\n", end_time-start_time);

    start_time = omp_get_wtime();
    for (p = 0; p < SIZE; p++)
        N[p] = M[p];
    end_time = omp_get_wtime();
    printf("Реальное время на замер времени for %.12lf\n", end_time-start_time);

    start_time = omp_get_wtime();
    memcpy(N, M, SIZE);
    end_time = omp_get_wtime();
    printf("Реальное время на замер времени memspy %.12lf\n", end_time-start_time);

    start_time = omp_get_wtime();
    #pragma omp parallel private(p)
    {
        p = omp_get_thread_num();
        size = omp_get_num_threads();
        memcpy(&N[p*SIZE/size], &M[p*SIZE/size], SIZE/size);
    }
    end_time = omp_get_wtime();
    printf("Реальное время на замер времени parallel memcpy %.12lf\n", end_time-start_time);

return 0;
}
