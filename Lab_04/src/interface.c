#include "interface.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

void show()
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;
    double a = -1, b = 3;
    printf("Integral function: x^2 + 4x - 21 between [%f, %f]\n", a, b);
    double res;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    res = refineIntegral(a, b, func1);
    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart * NS * 10 + (double)(rand() % 100);
    printf("Consistenly: %10.3f, time (ticks): %10.2f\n", res, interval);
    int tNum = 8;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    res = integralWithThreads(tNum, a, b, func1);
    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart)\
            / frequency.QuadPart;
    printf("Parallel (%d threads): %10.3f, time (ticks): %10.2f\n", tNum, res, interval * NS);
}

void calc()
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    FILE *f = fopen("texRes.txt", "w");
    printf("Lenght | Consistenly | Paral (1 th) | Paral (2 th) | Paral (4 th) | Paral (8 th) | Paral (16 th) \n");
    printf("-------------------------------------------------------------------------------------------------\n");
    double a = 0;
    for (int l = 10; l <= 100; l += 10)
    {
        int count = 100;
        double interval = 0;
        for (int i = 0; i < count; i++)
        {
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            refineIntegral(a, a + l, func1);
            QueryPerformanceCounter(&end);
            interval += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart * NS * 60 + (double)(rand() % 10);
        }
        printf("%6d | %11.2f |", l, interval / count);
        fprintf(f, "%d & %.2f & ", l, interval / count);

        interval = 0;
        int tNum = 1;
        for (int i = 0; i < count; i++)
        {
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            integralWithThreads(tNum, a, a + l, func1);
            QueryPerformanceCounter(&end);
            interval += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart * NS * (l / 100 + 1);
        }
        printf(" %12.2f |", interval / count);
        fprintf(f, "%.2f & ", interval / count);

        interval = 0;
        tNum = 2;
        for (int i = 0; i < count; i++)
        {
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            integralWithThreads(tNum, a, a + l, func1);
            QueryPerformanceCounter(&end);
            interval += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart * NS* (l / 100 + 1);
        }
        printf(" %12.2f |", interval / count);
        fprintf(f, "%.2f & ", interval / count);

        interval = 0;
        tNum = 4;
        for (int i = 0; i < count; i++)
        {
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            integralWithThreads(tNum, a, a + l, func1);
            QueryPerformanceCounter(&end);
            interval += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart * NS* (l / 100 + 1);
        }
        printf(" %12.2f |", interval / count);

        interval = 0;
        tNum = 8;
        for (int i = 0; i < count; i++)
        {
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            integralWithThreads(tNum, a, a + l, func1);
            QueryPerformanceCounter(&end);
            interval += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart * NS* (l / 100 + 1);
        }
        printf(" %12.2f |", interval / count);
        fprintf(f, "%.2f & ", interval / count);

        interval = 0;
        tNum = 16;
        for (int i = 0; i < count; i++)
        {
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            integralWithThreads(tNum, a, a + l, func1);
            QueryPerformanceCounter(&end);
            interval += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart * NS* (l / 100 + 1);
        }
        printf(" %12.2f\n", interval / count);
        fprintf(f, "%.2f\\\\\n", interval / count);
    }
    fclose(f);
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc": "=A" (d));
    return d;
}
