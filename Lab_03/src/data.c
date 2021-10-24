#include "data.h"

int *generateArray(int n)
{
    int *array = malloc(sizeof(int) * n);
    if (array)
        for (int i = 0; i < n; i++)
        {
            array[i] = rand() % 1000;
        }
    else
        printf("Ошибка данных");
    return array;
}

int *deepCopy(int *array, int n)
{
    int *arrCopy = malloc(sizeof(int) * n);
    if (arrCopy)
        for (int i = 0; i < n; i++)
        {
            arrCopy[i] = array[i];
        }
    else
        printf("Ошибка данных");
    return arrCopy;
}

void output(int *array, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void swap(int *a, int *b)
{
    int buf = *a;
    *a = *b;
    *b = buf;
}

int *reverse(int *array, int n)
{
    int *newArr = malloc(sizeof(int) * n);
    if (newArr)
    {
        for (int i = 0; i < n; i++)
        {
            newArr[i] = array[n - i - 1];
        }
        free(array);
    }
    else
        printf("Ошибка данных");
    return newArr;
}
