#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]){

    double start_time, end_time, tick;

    start_time = omp_get_wtime();
    tick = omp_get_wtick();
    end_time = omp_get_wtime();

    printf("Время на замер времени %.17lf\n", end_time-start_time);
    printf("Точность таймера %.17lf\n", tick);

    printf("Реальное время на замер времени %.12lf\n", tick *((int) ((end_time-start_time)/tick)) );

return 0;
}
