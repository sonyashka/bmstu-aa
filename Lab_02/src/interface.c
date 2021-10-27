#include "multiply.h"
#include "data.h"
#include "interface.h"

void show()
{
    int n = 3;
    int **A = generateMatrix(n, n);
    printf("A:\n");
    output(A, n, n);
    int **B = generateMatrix(n, n);
    printf("B:\n");
    output(B, n, n);
    int **C = multStand(A, B, n, n, n);
    int **D = multVin(A, B, n, n, n);
    int **E = multVinOptimize(A, B, n, n, n);
    printf("Standart multiply:\n");
    output(C, n, n);
    printf("Vinograd multiply:\n");
    output(D, n, n);
    printf("Vinograd-optimize multiply:\n");
    output(E, n, n);
    freeMatrix(A, n, n);
    freeMatrix(B, n, n);
    freeMatrix(C, n, n);
    freeMatrix(D, n, n);
    freeMatrix(E, n, n);
//    int **A = generateMatrix(5, 5);
//    printf("A:\n");
//    output(A, 5, 5);
//    int **B = generateMatrix(5, 5);
//    printf("B:\n");
//    output(B, 5, 5);
//    int **C = multStand(A, B, 5, 5, 5);
//    int **D = multVin(A, B, 5, 5, 5);
//    printf("Standart multiply:\n");
//    output(C, 5, 5);
//    printf("Vinograd multiply:\n");
//    output(D, 5, 5);
//    freeMatrix(A, 5, 5);
//    freeMatrix(B, 5, 5);
//    freeMatrix(C, 5, 5);
//    freeMatrix(D, 5, 5);
}

void calc()
{
    printf("Jopa\n");
    FILE *fBest = fopen("texBest.txt", "w");
    FILE *fWorst = fopen("texWorst.txt", "w");
    FILE *fBestStand = fopen("texBestStand.txt", "w");
    FILE *fBestVin = fopen("texBestVin.txt", "w");
    FILE *fBestVinOpt = fopen("texBestVinOpt.txt", "w");
    FILE *fWorstStand = fopen("texWorstStand.txt", "w");
    FILE *fWorstVin = fopen("texWorstVin.txt", "w");
    FILE *fWorstVinOpt = fopen("texWorstVinOpt.txt", "w");
    printf("BEST CASE (time in 1e6 tikcs)\n");
    printf("Size |    Standard    |    Vinograd     | VinogradOptimize\n");
    printf("----------------------------------------------------------\n");
    int **A, **B, **C;
    unsigned long timeEnd = 0, timeStart = 0, t1 = 0, t2 = 0, t3 = 0;
    for (int i = 50; i <= 700; i += 50)
    {
        printf("%4d |", i);
        fprintf(fBest, "%d & ", i);
        fprintf(fBestStand, "%d ", i);
        fprintf(fBestVin, "%d ", i);
        fprintf(fBestVinOpt, "%d ", i);
        int count = 10;
        for (int j = 0; j < count; j++)
        {
            A = generateMatrix(i, i);
            B = generateMatrix(i, i);
            timeStart = tick();
            C = multStand(A, B, i, i, i);
            timeEnd = tick();
            t1 += (timeEnd - timeStart) / 1e6;
            freeMatrix(C, i, i);

            timeStart = tick();
            C = multVin(A, B, i, i, i);
            timeEnd = tick();
            t2 += (timeEnd - timeStart) / 1e6;
            freeMatrix(C, i, i);

            timeStart = tick();
            C = multVinOptimize(A, B, i, i, i);
            timeEnd = tick();
            t3 += (timeEnd - timeStart) / 1e6;
            freeMatrix(C, i, i);
            freeMatrix(A, i, i);
            freeMatrix(B, i, i);
        }
        printf("%15ld | %15ld | %15ld\n", t1 / count, t2 / count, t3 / count);
        fprintf(fBest, "%ld000000 & %ld000000 & %ld000000\\\\\n", t1 / count, t2 / count, t3 / count);
        fprintf(fBestStand, "%ld000000\n", t1 / count);
        fprintf(fBestVin, "%ld000000\n", t2 / count);
        fprintf(fBestVinOpt, "%ld000000\n", t3 / count);
    }
    t1 = 0, t2 = 0, t3 = 0;
    printf("WORST CASE (time in 1e6 tikcs)\n");
    printf("Size |    Standard    |    Vinograd     | VinogradOptimize\n");
    printf("----------------------------------------------------------\n");
    for (int i = 51; i <= 701; i += 50)
    {
        printf("%4d |", i);
        fprintf(fWorst, "%d & ", i);
        fprintf(fWorstStand, "%d ", i);
        fprintf(fWorstVin, "%d ", i);
        fprintf(fWorstVinOpt, "%d ", i);
        int count = 10;
        for (int j = 0; j < count; j++)
        {
            A = generateMatrix(i, i);
            B = generateMatrix(i, i);
            timeStart = tick();
            C = multStand(A, B, i, i, i);
            timeEnd = tick();
            t1 += (timeEnd - timeStart) / 1e6;
            freeMatrix(C, i, i);

            timeStart = tick();
            C = multVin(A, B, i, i, i);
            timeEnd = tick();
            t2 += (timeEnd - timeStart) / 1e6;
            freeMatrix(C, i, i);

            timeStart = tick();
            C = multVinOptimize(A, B, i, i, i);
            timeEnd = tick();
            t3 += (timeEnd - timeStart) / 1e6;
            freeMatrix(C, i, i);
            freeMatrix(A, i, i);
            freeMatrix(B, i, i);
        }
        printf("%15ld | %15ld | %15ld\n", t1 / count, t2 / count, t3 / count);
        fprintf(fWorst, "%ld000000 & %ld000000 & %ld000000\\\\\n", t1 / count, t2 / count, t3 / count);
        fprintf(fWorstStand, "%ld000000\n", t1 / count);
        fprintf(fWorstVin, "%ld000000\n", t2 / count);
        fprintf(fWorstVinOpt, "%ld000000\n", t3 / count);
    }
    fclose(fBest);
    fclose(fWorst);
    fclose(fBestStand);
    fclose(fBestVin);
    fclose(fBestVinOpt);
    fclose(fWorstStand);
    fclose(fWorstVin);
    fclose(fWorstVinOpt);
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc": "=A" (d));
    return d;
}
