#ifndef ALGORITM_C
#define ALGORITM_C

#include <stdio.h>
#include <stdlib.h>

#define MAX_LIM 1000

int levCacheTwoRows(char *s1, int i, char *s2, int j);
int levRecWithoutCache(char *s1, int i, char *s2, int j);
int levRecMakeCache(char *s1, int i, char *s2, int j);
int levRecWithCache(char *s1, int i, char *s2, int j, int *cache, int cacheSize);
int damLevRecWithoutCache(char *s1, int i, char *s2, int j);
int min(int a, int b, int c);

#endif // ALGORITM_C
