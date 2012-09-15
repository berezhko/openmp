#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define M 800

double MA[M][M+1];

int printMatrix(){
    int k, d;
    for (k = 0; k < M; k++){
        for (d = 0; d <= M; d++){
            printf("%.9f ", MA[k][d]);
        }
        printf("\n");
    }
    printf("\n");

return 0;
}

int main(int args, char **argv){
    int i, j;
    struct timespec tp;

    clock_gettime (CLOCK_REALTIME, &tp);
    srand((int)tp.tv_nsec);

    for (i = 0; i < M; i++){
        for (j = 0; j < M; j++){
            MA[i][j] = rand()/(double)RAND_MAX*10.0;
        }
        MA[i][M] = i;
    }

    printMatrix();

return 0;
}
