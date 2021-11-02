﻿#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n = 3;                                      // (1)
    int **matrix = malloc(sizeof(int *) * n);       // (2)
    for (int i = 0; i < n; i++)                     // (3)
    {
        matrix[i] = malloc(sizeof(int) * n);        // (4)
        for (int j = 0; j < n; j++)                 // (5)
            matrix[i][j] = rand() % 10;             // (6)
    }
    int res = 0, p1, p2, k1, k2;                    // (7)
    for (int i = 0; i < n; i++)                     // (8)
    {
        p1 = p2 = 1;                                // (9)
        k1 = k2 = i;                                // (10)
        for (int j = 0; j < n; j++)                 // (11)
        {
            if (++k1 == n)                          // (12)
                k1 = 0;                             // (13)
            if (--k2 == -1)                         // (14)
                k2 = n - 1;                         // (15)
            p1 *= matrix[j][k1];                    // (16)
            p2 *= matrix[j][k2];                    // (17)
        }
        res += p1 - p2;                             // (18)
    }
    printf("%d\n", res);
    for (int i = 0; i < n; i++)                     // (19)
        free(matrix[i]);                            // (20)
    free(matrix);                                   // (21)
    return 0;
}
