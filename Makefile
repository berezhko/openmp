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

mp-6:
	$(CC) $(OMP) omp-6.c -o omp-6

mp-7:
	$(CC) $(OMP) omp-7.c -o omp-7

mp-8:
	$(CC) $(OMP) omp-8.c -o omp-8

mp-9:
	$(CC) $(OMP) omp-9.c -o omp-9

mp-10:
	$(CC) $(OMP) omp-10.c -o omp-10

mp-11:
	$(CC) $(OMP) omp-11.c -o omp-11

mp-12:
	$(CC) $(OMP) omp-12.c -o omp-12

mp-13:
	$(CC) $(OMP) omp-13.c -o omp-13

mp-14:
	$(CC) $(OMP) omp-14.c -o omp-14

mp-15:
	$(CC) $(OMP) omp-15.c -o omp-15

mp-16:
	$(CC) $(OMP) omp-16.c -o omp-16

mp-17:
	$(CC) $(OMP) omp-17.c -o omp-17

mp-18:
	$(CC) $(OMP) omp-18.c -o omp-18

mp-19:
	$(CC) $(OMP) omp-19.c -o omp-19

mp-20:
	$(CC) $(OMP) omp-20.c -o omp-20

