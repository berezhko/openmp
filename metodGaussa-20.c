#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <string.h>

#define M 2000

long double MA[M][M+1], MA2[M][M+1], V[M+1], X[M], MAD, OTV[M];

int printMatrix(){

return 0;

    int k, d;
    for (k = 0; k < M; k++){
        for (d = 0; d <= M; d++){
            printf("%.2Lf ", MA[k][d]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int args, char **argv){
    int size, i, j, v, k, d, p, J;

    int * mas;
    long double MAX;
    double wtime1, wtime2, wtick;


    for (i = 0; i < M; i++){
        for (j = 0; j <= M; j++){
            fscanf(stdin, "%Lf", &MA[i][j]);
        }
    }

    printMatrix();

    memcpy(MA2, MA, sizeof(long double)*M*(M+1));

    wtime1 = omp_get_wtime();
    for (i = 0; i < M; i++){

        printMatrix();

        MAX = fabsl(MA[i][i]);
        J = i;
        for (j = i+1; j < M; j++){
            if (fabsl(MA[j][i]) > MAX){
                MAX = fabsl(MA[j][i]);
                J = j;
            }
        }

        if (J != i){
            memcpy(V, &MA[i][i], sizeof(long double)*(M+1-i));
            memcpy(&MA[i][i], &MA[J][i], sizeof(long double)*(M+1-i));
            memcpy(&MA[J][i], V, sizeof(long double)*(M+1-i));
        }

        printMatrix();

        if (MA[i][i] != 0){
            for (j = M; j >= i; j--)
                MA[i][j] /= MA[i][i];
        }else{
            fprintf(stderr, "Система не совместна\nMA[%d]=%.2Lf MA[%d][%d] = %.2Lf\n", i, MA[i][i], i, j, MA[i][j]);
            return 0;
        }

        printMatrix();
 
        for (k = i+1; k < M; k++){
            for (d = M; d >= i; d--){
                //printf("%d: %d %d\n", k, d);
//                printf("MA[%d][%d] = %.2f -= MA[%d][%d] = %.2f * MA[%d][%d] = %.2f\n", k, d, MA[k][d], k, i, MA[k][i], i, d, MA[i][d]);
                MA[k][d] -= MA[k][i]*MA[i][d];
            }
        }

        printMatrix();
    }

    for ( i = 0; i < M; i++ )
        X[i] = MA[i][M];

    for ( i = M - 2; i >= 0; i-- )
        for ( j = i + 1; j < M; j++ )
            X[i] -= X[j] * MA[i][j];
    wtime2 = omp_get_wtime();

    fprintf(stderr, "Время работы программы %.9f\n", wtime2-wtime1);

    for (i = 0; i < M; i++){
        MAD = 0;
        for (j = 0; j < M; j ++){
            MAD += MA2[i][j]*X[j];
        }
        MAD -= MA2[i][M];
        if (i < M-1)
            printf("%.12Lf+", MAD);
        else
            printf("%.12Lf\n", MAD);
    }
    printf("\n");


return 0;
}
