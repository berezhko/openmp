#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
int i, m[10];
printf("Массив m в начале:\n");
/* Заполним массив m нулями и напечатаем его */
for (i=0; i<10; i++){
m[i]=0;
printf("%d\n", m[i]);
}
#pragma omp parallel shared(m)
{
/* Присвоим 1 элементу массива m, номер которого
 * совпадает с номером текущий нити */
m[omp_get_thread_num()]=1;
}
/* Ещё раз напечатаем массив */
printf("Массив m в конце:\n");
for (i=0; i<10; i++) printf("%d\n", m[i]);
}
