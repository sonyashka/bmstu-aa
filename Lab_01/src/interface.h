#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "algoritm.h"

#define MAX_LEN 100

void show();
void calc();
char *strInput();
char *generateStr(int n);
unsigned long long tick(void);

#endif // INTERFACE_H
