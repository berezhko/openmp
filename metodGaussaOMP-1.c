#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <string.h>

#define M 800

double MA[M][M+1], MA2[M][M+1], V[M+1], X[M], MAD, OTV[M];

int printMatrix(){
    int k, d;

return 0;

    for (k = 0; k < M; k++){
        for (d = 0; d <= M; d++){
            printf("%.2f ", MA[k][d]);
        }
        printf("\n");
    }
    printf("\n");

return 0;
}

int main(int args, char **argv){
    int size, MyP, i, j, v, k, d, p, J;

    int * mas;
    double MAX;
    double wtime1, wtime2, wtick;


/* Каждая ветвь генерирует свою полосу матрицы A и свой отрезок вектора
 * правой части, который присоединяется дополнительным столбцом к A.
 * Нулевая ветвь генерирует нулевую полосу, первая ветвь - первую полосу
 * и т.д. (По диагонали исходной матрицы - числа = 2, остальные числа = 1). */
    wtime1 = omp_get_wtime();
    wtick = omp_get_wtick();
    wtime2 = omp_get_wtime();
    srand((int)((wtime2-wtime1)/wtick));

    #pragma omp for
    for (i = 0; i < M; i++){
        for (j = 0; j < M; j++){
            MA[i][j] = rand()/(double)RAND_MAX*10.0;
        }
        MA[i][M] = i;
    }

    printMatrix();

    memcpy(MA2, MA, sizeof(double)*M*(M+1));

    for (i = 0; i < M; i++ )
        OTV[i] = i;

    wtime1 = omp_get_wtime();
    for (i = 0; i < M; i++){


        #pragma omp parallel shared(mas, size, i, MA, MAD) private(j, MyP, MAX)
        {
            MyP = omp_get_thread_num();
            #pragma omp single
            {
                size = omp_get_num_threads();
                mas = malloc(sizeof(int)*size);
            }

            MAX = fabs(MA[i][i]);
            mas[MyP] = i;

            #pragma omp for
            for (j = i+1; j < M; j++){
                if (fabs(MA[j][i]) > MAX){
                    MAX = fabs(MA[j][i]);
                    mas[MyP] = j;
                }
            }

            #pragma omp single
            {
                J = i;
                MAX = fabs(MA[J][i]);
                for (j = 0; j < size; j++){
                    if (fabs(MA[mas[j]][i]) > MAX){
                        J = mas[j];
                        MAX = fabs(MA[J][i]);
                    }
                }
                if (J != i){
                    memcpy(V, &MA[i][i], sizeof(double)*(M+1-i));
                    memcpy(&MA[i][i], &MA[J][i], sizeof(double)*(M+1-i));
                    memcpy(&MA[J][i], V, sizeof(double)*(M+1-i));
                }
                free(mas);
                printMatrix();
            }

            #pragma omp for
            for (j = M; j > i; j--){

                if (MA[i][i] != 0){
                    //printf("%d: MA[%d][%d] = %.2f\n", MyP, i, j, MA[i][j]);
                    MA[i][j] /= MA[i][i];
                    //printf("%d: MA[%d][%d] = %.2f\n", MyP, i, j, MA[i][j]);
                }else
                    printf("ERROR DIV BY ZERO %d: MA[%d][%d] = %.2f\n", MyP, i, j, MA[i][j]);
            }

            #pragma omp master
                MA[i][i] = 1;
            
            #pragma omp single
            {
                printMatrix();
            }
 
            #pragma omp for private(d)
            for (k = i+1; k < M; k++){
                for (d = M; d >= i; d--){
                    //printf("%d: %d %d\n", MyP, k, d);
                    //printf("%d: MA[%d][%d] = %.2f -= MA[%d][%d] = %.2f * MA[%d][%d] = %.2f\n", MyP, k, d, MA[k][d], k, i, MA[k][i], i, d, MA[i][d]);
                    MA[k][d] -= MA[k][i]*MA[i][d];
                }
            }

            #pragma omp single
            {
                printMatrix();
            }
        }
    }

    #pragma omp for
    for ( i = 0; i < M; i++ )
        X[i] = MA[i][M];

    for ( i = M - 2; i >= 0; i-- )
        for ( j = i + 1; j < M; j++ )
            X[i] -= X[j] * MA[i][j];
    wtime2 = omp_get_wtime();

    //printf("Время работы программы %.9f\n", wtime2-wtime1);

    for (i = 0; i < M; i++){
        MAD = 0;
        for (j = 0; j < M; j ++){
            MAD += MA2[i][j]*X[j];
        }
        MAD -= MA2[i][M];
        if (i < M-1)
            printf("%.9f+", MAD);
        else
            printf("%.9f\n", MAD);
    }
    //printf("\n");


return 0;
}
