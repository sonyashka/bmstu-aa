#include "sorting.h"
#include "data.h"
#include "interface.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

void show()
{
    int *array = generateArray(10);
    printf("Original array:         ");
    output(array, 10);

    int *a = deepCopy(array, 10);
    a = bubbleSort(a, 10);
    printf("Bubble-sorted array:    ");
    output(a, 10);
    free(a);

    a = deepCopy(array, 10);
    a = insertionSort(a, 10);
    printf("Insertion-sorted array: ");
    output(a, 10);
    free(a);

    a = deepCopy(array, 10);
    a = selectionSort(a, 10);
    printf("Selection-sorted array: ");
    output(a, 10);
    free(a);
    free(array);
}

void calc()
{
    FILE *fRand = fopen("texRand.txt", "w");
    FILE *fSorted = fopen("texSorted.txt", "w");
    FILE *fRevSorted = fopen("texRevSorted.txt", "w");
    printf("Size |  Bubble  |  Insert  | Selection |  Bubble  |  Insert  | Selection |  Bubble  |  Insert  | Selection |\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
    int *array, *arrSorted, *arrRevSorted, *a, *b, *c;
    unsigned long timeEnd = 0, timeStart = 0, t1 = 0, t2 = 0, t3 = 0;
    for (int i = 50; i < 700; i += 50)
    {
        printf("%4d |", i);
        fprintf(fRand, "%d & ", i);
        fprintf(fSorted, "%d & ", i);
        fprintf(fRevSorted, "%d & ", i);
        for (int j = 0; j < 1000; j++)
        {
            array = generateArray(i);
            a = deepCopy(array, i);
            timeStart = tick();
            a = bubbleSort(a, i);
            timeEnd = tick();
            t1 += timeEnd - timeStart;
            free(a);

            b = deepCopy(array, i);
            timeStart = tick();
            b = insertionSort(b, i);
            timeEnd = tick();
            t2 += timeEnd - timeStart;
            free(b);

            c = deepCopy(array, i);
            timeStart = tick();
            c = selectionSort(c, i);
            timeEnd = tick();
            t3 += timeEnd - timeStart;
            free(c);
            free(array);
        }
        printf("%10ld %10ld %10ld |", t1 / 1000, t2 / 1000, t3 / 1000);
        fprintf(fRand, "%ld & %ld & %ld\\\\\n", t1 / 1000, t2 / 1000, t3 / 1000);
//        fprintf(fBubble, "%ld & ", t1 / 1000);
//        fprintf(fInsert, "%ld & ", t2 / 1000);
//        fprintf(fSelection, "%ld & ", t3 / 1000);
        t1 = 0, t2 = 0, t3 = 0;

        for (int j = 0; j < 1000; j++)
        {
            array = generateArray(i);
            arrSorted = insertionSort(deepCopy(array, i), i);
            a = deepCopy(arrSorted, i);
            timeStart = tick();
            a = bubbleSort(a, i);
            timeEnd = tick();
            t1 += timeEnd - timeStart;
            free(a);

            b = deepCopy(arrSorted, i);
            timeStart = tick();
            b = insertionSort(b, i);
            timeEnd = tick();
            t2 += timeEnd - timeStart;
            free(b);

            c = deepCopy(arrSorted, i);
            timeStart = tick();
            c = selectionSort(c, i);
            timeEnd = tick();
            t3 += timeEnd - timeStart;
            free(c);
            free(array);
            free(arrSorted);
        }
        printf("%10ld %10ld %10ld |", t1 / 1000, t2 / 1000, t3 / 1000);
        //fprintf(f, "%ld & %ld & %ld & ", t1 / 1000, t2 / 1000, t3 / 1000);
        fprintf(fSorted, "%ld & %ld & %ld\\\\\n", t1 / 1000, t2 / 1000, t3 / 1000);
//        fprintf(fBubble, "%ld & ", t1 / 1000);
//        fprintf(fInsert, "%ld & ", t2 / 1000);
//        fprintf(fSelection, "%ld & ", t3 / 1000);
        t1 = 0, t2 = 0, t3 = 0;

        for (int j = 0; j < 1000; j++)
        {
            array = generateArray(i);
            arrSorted = insertionSort(deepCopy(array, i), i);
            arrRevSorted = reverse(arrSorted, i);
            a = deepCopy(arrRevSorted, i);
            timeStart = tick();
            a = bubbleSort(a, i);
            timeEnd = tick();
            t1 += timeEnd - timeStart;
            free(a);

            b = deepCopy(arrRevSorted, i);
            timeStart = tick();
            b = insertionSort(b, i);
            timeEnd = tick();
            t2 += timeEnd - timeStart;
            free(b);

            c = deepCopy(arrRevSorted, i);
            timeStart = tick();
            c = selectionSort(c, i);
            timeEnd = tick();
            t3 += timeEnd - timeStart;
            free(c);
            free(array);
            free(arrRevSorted);
        }
        printf("%10ld %10ld %10ld |\n", t1 / 1000, t2 / 1000, t3 / 1000);
        //fprintf(f, "%ld & %ld & %ld\\\\\n", t1 / 1000, t2 / 1000, t3 / 1000);
        fprintf(fRevSorted, "%ld & %ld & %ld\\\\\n", t1 / 1000, t2 / 1000, t3 / 1000);
//        fprintf(fBubble, "%ld\\\\\n", t1 / 1000);
//        fprintf(fInsert, "%ld\\\\\n", t2 / 1000);
//        fprintf(fSelection, "%ld\\\\\n", t3 / 1000);
        t1 = 0, t2 = 0, t3 = 0;
        //free(array);
        //free(arrRevSorted);
    }
    fclose(fRand);
    fclose(fSorted);
    fclose(fRevSorted);
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc": "=A" (d));
    return d;
}
