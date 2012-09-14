#include <stdio.h>
#include <omp.h>

int main(){
    int i;
    int p;

#pragma omp parallel private(p)
{
    p = omp_get_thread_num();
    #pragma omp for
    for(i=0; i < 10; i++){
        printf("%d %d\n", i, p);
    }
}

return 0;
}
