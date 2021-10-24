#include "interface.h"

void show()
{
    printf("Input first word: ");
    char *str1 = strInput();
    int len1 = strlen(str1);
    printf("Input second word: ");
    char *str2 = strInput();
    int len2 = strlen(str2);
    printf("levCacheTwoRows = %d\n"
           "levRecWithoutCache = %d\n"
           "levRecWithCache = %d\n" ""
           "damLevRecWithoutCache = %d\n",
           levCacheTwoRows(str1, len1, str2, len2),\
           levRecWithoutCache(str1, len1, str2, len2),\
           levRecMakeCache(str1, len1, str2, len2),\
           damLevRecWithoutCache(str1, len1, str2, len2));
    free(str1);
    free(str2);
}

void calc()
{
    FILE *f = fopen("texTbl.txt", "w");
    printf("Size|LevCache2Row| LevRecNotC | LevRecWithC|DamLevRecNotC\n");
    printf("---------------------------------------------------------\n");
    unsigned long timeEnd = 0, timeStart = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    for (int i = 1; i < 10; i++)
    {
       printf("%4d| ", i);
       fprintf(f, "%d & ", i);
       for (int j = 0; j < 100; j++)
       {
           char *str1 = generateStr(i);
           char *str2 = generateStr(i + 1);
           timeStart = tick();
           levCacheTwoRows(str1, i, str2, i + 1);
           timeEnd = tick();
           t1 += timeEnd - timeStart;

           timeStart = tick();
           levRecWithoutCache(str1, i, str2, i + 1);
           timeEnd = tick();
           t2 += timeEnd - timeStart;

           timeStart = tick();
           levRecMakeCache(str1, i, str2, i + 1);
           timeEnd = tick();
           t3 += timeEnd - timeStart;

           timeStart = tick();
           damLevRecWithoutCache(str1, i, str2, i + 1);
           timeEnd = tick();
           t4 += timeEnd - timeStart;

           free(str1);
           free(str2);
       }
       fprintf(f, "%ld & %ld & %ld & %ld\\\\\n", t1 / 100, t2 / 100, t3 / 100, t4 / 100);
       printf("%10ld | %10ld | %10ld | %10ld\n", t1 / 100, t2 / 100, t3 / 100, t4 / 100);
       t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    }
    fclose(f);
}

char *strInput()
{
    char *str = malloc(sizeof(char) * MAX_LEN);
    if (!str)
        return NULL;

    fflush(stdin);
    fgets(str, MAX_LEN, stdin);
    return str;
}

char *generateStr(int n)
{
    char *str = malloc(sizeof(char) * n);
    if (!str)
        return NULL;

    for (int i = 0; i < n - 1; i++)
    {
        str[i] = 97 + rand() % 26;
    }
    str[n - 1] = '\0';
    return str;
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc": "=A" (d));
    return d;
}
