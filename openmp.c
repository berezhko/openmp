#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <malloc.h>

int main (int argc, char *argv[]){

    int i, j, k;
    float *a, *b, *c, sum;
    struct timeval timev1, timev2;
    float time_seconds;

    int N = atoi(argv[1]);
    int P = atoi(argv[2]);
    printf("N=%d P=%d\n", N, P);

    a = (float*) malloc(N*N*sizeof(float));
    b = (float*) malloc(N*N*sizeof(float));
    c = (float*) malloc(N*N*sizeof(float));

    for( i = 0; i < N*N; i++) {
        a[i] = 0.1;
        b[i] = 0.2;
        c[i] = 0.0;
    }

    omp_set_num_threads(P);

    sum = 0;
    #pragma omp parallel for
    for (i = 0; i < N; i++){
        sum += i;
        printf("%d\n", i);
    }

    printf("%d\n", sum);
    free(a);
    free(b);
    free(c);

return 0;
}
