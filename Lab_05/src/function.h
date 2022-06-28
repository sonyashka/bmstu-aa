#ifndef FUNCTION_H
#define FUNCTION_H

#include "interface.h"
#include <pthread.h>

struct flItem
{
    int n;
    int **m1;
    int **m2;
    int **res;
    struct flItem *next;
};

struct slItem
{
    int n;
    int **m;
    int res;
    struct slItem *next;
};

struct tlItem
{
    int n;
    int res;
    struct tlItem *next;
};

struct reslItem
{
    int res;
    struct reslItem *next;
};

struct queue
{
    int num;
    struct flItem *fstart;
    struct flItem *fend;
    struct slItem *sstart;
    struct slItem *send;
    struct tlItem *tstart;
    struct tlItem *tend;
    struct reslItem *resstart;
    struct reslItem *resend;
    pthread_mutex_t m1;
    pthread_mutex_t m2;
    pthread_mutex_t m3;
    pthread_mutex_t resm;
    int startTime;
    int fileMatrix[1000][3][2];
//    int q1[1000][3];
//    int q2[1000][3];
//    int q3[1000][3];
};

void firstPush(struct queue *data, int n);
void firstPop(struct queue *data);
void secondPush(struct queue *data);
void secondPop(struct queue *data);
void thirdPush(struct queue *data);
void thirdPop(struct queue *data);
void resPush(struct queue *data);
int resPop(struct queue *data);

void startPipeline(int n, int size);
void startPipelineCalc(int n, int size);
void *startFirst(void *firstData);
void *startSecond(void *secondData);
void *startThird(void *thirdData);

int **allocMatrix(int n);
void freeMatrix(int n, int **m);
void fillMatrix(int n, int **m);
void outputMatrix(int n, int **m);
void multMatrix(int n, int **m1, int **m2, int **res);
int determinator(int n, int **m);
int prime(int n);

#endif // FUNCTION_H
