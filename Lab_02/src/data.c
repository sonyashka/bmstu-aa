#include "data.h"

int **allocateMatrix(int m, int n)
{
    int **matrix = malloc(sizeof(int *) * m);
    int flag = 1;
    if (matrix)
    {
        for (int i = 0; i < m && flag; i++)
        {
            matrix[i] = malloc(sizeof(int) * n);
            if (!matrix)
                flag = 0;
        }
        if (!flag)
            printf("Ошибка данных\n");
    }
    else
        printf("Ошибка данных\n");
    return matrix;
}

void freeMatrix(int **matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
        free(matrix[i]);
    free(matrix);
}

int **generateMatrix(int m, int n)
{
    int **matrix = allocateMatrix(m, n);
    if (matrix)
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                matrix[i][j] = rand() % 5;
        }
    else
        printf("Ошибка данных\n");
    return matrix;
}

int **deepCopy(int **matrix, int m, int n)
{
    int **matrixCopy = allocateMatrix(m, n);
    if (matrixCopy)
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                matrixCopy[i][j] = matrix[i][j];
        }
    else
        printf("Ошибка данных\n");
    return matrixCopy;
}

void output(int **matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%6d ", matrix[i][j]);
        printf("\n");
    }
}

void swap(int *a, int *b)
{
    int buf = *a;
    *a = *b;
    *b = buf;
}
