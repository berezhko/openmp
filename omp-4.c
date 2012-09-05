#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]){
    int n;

    omp_set_nested(1);
#pragma omp parallel private(n)
    {
        n=omp_get_thread_num();
#pragma omp parallel
        {
            printf("Часть 1, нить %d - %d\n", n,
            omp_get_thread_num());
        }
    }

    omp_set_nested(0);
#pragma omp parallel private(n)
    {
        n=omp_get_thread_num();
#pragma omp parallel
        {
            printf("Часть 2, нить %d - %d\n", n,
            omp_get_thread_num());
        }
    }

return 0;
}
