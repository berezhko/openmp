CC=gcc
LD=-lm -lrt
OMP=-O3 -fopenmp

omp:
	$(CC) $(OMP) openmp.c -o openmp

mp-1:
	$(CC) $(OMP) omp-1.c -o omp-1

mp-2:
	$(CC) $(OMP) omp-2.c -o omp-2

mp-3:
	$(CC) $(OMP) omp-3.c -o omp-3

mp-4:
	$(CC) $(OMP) omp-4.c -o omp-4

mp-5:
	$(CC) $(OMP) omp-5.c -o omp-5
