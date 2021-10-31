#ifndef INTERFACE_H
#define INTERFACE_H

#define NS 1e6

#include "integral.h"
#include <sys/time.h>
#include <time.h>
#include <windows.h>

void show();
void calc();
unsigned long long tick(void);

#endif // INTERFACE_H
