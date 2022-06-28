#ifndef INTERFACE_H
#define INTERFACE_H

#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct listElem
{
    int **m1;
    int **m2;
    int **mRes;
    int *det;
    struct listElem *next;
};

void show();
void calc();
unsigned long long tick(void);

#endif // INTERFACE_H
