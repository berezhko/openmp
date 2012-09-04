CC=gcc
LD=-lm -lrt
OMP=-O3 -fopenmp

omp:
	$(CC) $(OMP) openmp.c -o openmp
