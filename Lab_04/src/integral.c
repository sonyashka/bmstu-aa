#include "integral.h"

double func1(double x)
{
    return x * x + 4 * x - 21;
}

double func2(double x)
{
    return x - 130;
}

double func3(double x)
{
    return -x * x * x + 7;
}

double calculateIntegral(double a, double b, int n, integralFunc func)
{
    double result = 0;
    double h = (b - a) / n;
    double curX = a;
    for (int i = 1; i < n; i++)
    {
        curX += h;
        result += func(curX);
    }
    result += (func(a) + func(b)) / 2;
    result *= h;
    return result;
}

double refineIntegral(double a, double b, integralFunc func)
{
    int n = 2;
    double refRes = calculateIntegral(a, b, n, func);
    double res = 0;
    while (fabs(res - refRes) > EPS)
    {
        res = refRes;
        n *= 2;
        refRes = calculateIntegral(a, b, n, func);
    }
    return res;
}

double integralWithThreads(int tNum, double a, double b, integralFunc func)
{
    double h = (b - a) / tNum;
    pthread_t threads[tNum];
    struct threadData threadData[tNum];
    for (int i = 0; i < tNum; i++)
    {
        threadData[i].ind = i;
        threadData[i].a = a;
        threadData[i].h = h;
        threadData[i].func = func;
        threadData[i].res = 0;
        pthread_create(&(threads[i]), NULL,\
                       oneThreadIntegral, &threadData[i]);
    }

    for (int i = 0; i < tNum; i++)
        pthread_join(threads[i], NULL);

    double res = 0;
    for (int i = 0; i < tNum; i++)
        res += threadData[i].res;
    return res;
}

void *oneThreadIntegral(void *threadData)
{
    struct threadData *data = (struct threadData *) threadData;
    double start = data->a + data->ind * data->h;
    data->res = refineIntegral(start, start + data->h, data->func);
    return NULL;
}
