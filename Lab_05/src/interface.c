#include "interface.h"
#include "function.h"

void show()
{
    int n = 10, size = 3;
    startPipeline(n, size);
}

void calc()
{
    int n = 20, size = 3;
    startPipelineCalc(n, size);
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc": "=A" (d));
    return d;
}
