#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>

int **allocateMatrix(int m, int n);
void freeMatrix(int **matrix, int m, int n);
int **generateMatrix(int m, int n);
int **deepCopy(int **matrix, int m, int n);
void output(int **matrix, int m, int n);
void swap(int *a, int *b);

#endif // DATA_H
