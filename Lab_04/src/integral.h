#ifndef INTEGRAL_H
#define INTEGRAL_H

#define EPS 1e-3

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

typedef double(*integralFunc)(double);

struct threadData{
    int ind;
    double a;
    double h;
    integralFunc func;
    double res;
};

double func1(double x);
double func2(double x);
double func3(double x);
double calculateIntegral(double a, double b, int n, integralFunc func);
double refineIntegral(double a, double b, integralFunc func);
double integralWithThreads(int tNum, double a, double b, integralFunc func);
void *oneThreadIntegral(void *threadData);

#endif // INTEGRAL_H
