#include "algoritm.h"

int levCacheTwoRows(char *s1, int i, char *s2, int j)
{
    int *a1 = malloc(sizeof(int) * (j + 1));
    int *a2 = malloc(sizeof(int) * (j + 1));
    if (!a1 && !a2)
        return -1;

    for (int m = 0; m < j + 1; m++)
        a1[m] = m;

    int flag;
    for (int m = 1; m < i + 1; m++)
    {
        a2[0] = a1[0] + 1;
        for (int n = 1; n < j + 1; n++)
        {
            if (s1[m - 1] == s2[n - 1])
                flag = 0;
            else
                flag = 1;
            a2[n] = min(a2[n - 1] + 1, a1[n] + 1, a1[n - 1] + flag);
        }
        for (int n = 0; n < j + 1; n++)
            a1[n] = a2[n];
    }
    int result = a2[j];
    free(a1);
    free(a2);
    return result;
}

int levRecWithoutCache(char *s1, int i, char *s2, int j)
{
    if (i == 0)
        return j;
    else if (j == 0)
        return i;

    int flag;
    if (s1[i - 1] == s2[j - 1])
        flag = 0;
    else
        flag = 1;
    int result = min(levRecWithoutCache(s1, i - 1, s2, j) + 1,\
                     levRecWithoutCache(s1, i, s2, j - 1) + 1,\
                     levRecWithoutCache(s1, i - 1, s2, j - 1) + flag);
    return result;
}

int levRecMakeCache(char *s1, int i, char *s2, int j)
{
    int cacheSize = (j + 1) * (i + 1);
    int *cache = malloc(sizeof(int) * cacheSize);
    if (!cache)
        return -1;

    for (int m = 0; m < cacheSize; m++)
        cache[m] = MAX_LIM;
    int result = levRecWithCache(s1, i, s2, j, cache, j + 1);
    free(cache);
    return result;
}

int levRecWithCache(char *s1, int i, char *s2, int j, int *cache, int cacheSize)
{
    if (i == 0)
        return j;
    else if (j == 0)
        return i;

    if (cache[i * cacheSize + j] < MAX_LIM)
        return cache[i * cacheSize + j];

    int flag;
    if (s1[i - 1] == s2[j - 1])
        flag = 0;
    else
        flag = 1;
    cache[i * cacheSize + j] = min(levRecWithCache(s1, i - 1, s2, j, cache, cacheSize) + 1,\
                     levRecWithCache(s1, i, s2, j - 1, cache, cacheSize) + 1,\
                     levRecWithCache(s1, i - 1, s2, j - 1, cache, cacheSize) + flag);
    return cache[i * cacheSize + j];
}

int damLevRecWithoutCache(char *s1, int i, char *s2, int j)
{
    if (i == 0)
        return j;
    else if (j == 0)
        return i;

    int flag;
    if (s1[i - 1] == s2[j - 1])
        flag = 0;
    else
        flag = 1;
    int res1 = damLevRecWithoutCache(s1, i - 1, s2, j) + 1;
    int res2 = damLevRecWithoutCache(s1, i, s2, j - 1) + 1;
    int res3 = damLevRecWithoutCache(s1, i - 1, s2, j - 1) + flag;

    int result = min(res1, res2, res3);
    if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
        result = min(result, damLevRecWithoutCache(s1, i - 2, s2, j - 2) + 1, MAX_LIM);
    return result;
}

int min(int a, int b, int c)
{
    if (a <= b && a <= c)
        return a;
    if (b <= a && b <= c)
        return b;
    return c;
}
