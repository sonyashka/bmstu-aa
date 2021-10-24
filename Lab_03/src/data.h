#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>

int *generateArray(int n);
int *deepCopy(int *array, int n);
void output(int *array, int n);
void swap(int *a, int *b);
int *reverse(int *array, int n);

#endif // DATA_H
