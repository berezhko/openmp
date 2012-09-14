#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <string.h>

#define M 6

double MA[M][M+1], V[M+1], MAD, OTV[M];
 

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

    for (i = 0; i < M; i++ )
        OTV[i] = i;

    for (i = 0; i < M-1; i++){

        for (k = 0; k < M; k++){
            for (d = 0; d <= M; d++){
                printf("%.2f ", MA[k][d]);
            }
            printf("\n");
        }
        printf("\n");


        #pragma omp parallel shared(mas, size, i) private(j, MyP, MAX)
        {
            MyP = omp_get_thread_num();
            #pragma omp single
            {
                size = omp_get_num_threads();
                mas = malloc(sizeof(int)*size);
            }

            MAX = fabs(MA[i][i]);
            mas[MyP] = i;

            //#pragma omp barrier
            #pragma omp for
            for (j = i+1; j < M; j++){
            //    printf("%d %d\n", MyP, j);
                if (fabs(MA[j][i]) > MAX){
                    MAX = fabs(MA[j][i]);
                    mas[MyP] = j;
                }
            }

            #pragma omp barrier
            //printf("%d: MA[%d] = %.2f\n", MyP,  mas[MyP], MAX);
            //#pragma omp barrier

            #pragma omp master
            {
            //    printf("\n");

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
            }
        }
    }


    for (i = 0; i < M; i++){
        for (j = 0; j <= M; j ++){
            printf("%.2f ", MA[i][j]);
        }
        printf("\n");
    }


return 0;
}
