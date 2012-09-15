#include <stdio.h>
#include <omp.h>

int main(){
    int i;
    int p;
    int MAD;

#pragma omp parallel private(p)
{
    p = omp_get_thread_num();
    MAD = 13;
    #pragma omp for
    for(i=0; i < 10; i++){
        printf("%d %d %d\n", p, i, MAD);
    }
}

return 0;
}
