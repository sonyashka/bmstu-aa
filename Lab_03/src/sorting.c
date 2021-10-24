#include "sorting.h"
#include "data.h"

int *bubbleSort(int *array, int n)
{
    for (int i = n - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
        {
            if (array[j] > array[j + 1])
               swap(&array[j], &array[j + 1]);
        }
    return array;
}

int *insertionSort(int *array, int n)
{
    int j, buf;
    for (int i = 2; i < n; i++)
    {
        if (array[i] < array[i - 1])
        {
            buf = array[i];
            j = i - 1;
            while (j >= 0 && array[j] > buf)
            {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = buf;
        }
    }
    return array;
}

int *selectionSort(int *array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = array[i], ind = i;
        for (int j = i + 1; j < n; j++)
            if (array[j] < min)
            {
                min = array[j];
                ind = j;
            }
        swap(array + i, array + ind);
    }
    return array;
}
