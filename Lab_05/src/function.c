#include "function.h"

void multMatrix(int n, int **m1, int **m2, int **res)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < n; k++)
                res[i][j] += m1[i][k] * m2[k][j];
        }
    }
}

int determinator(int n, int **m)
{
    int sum = 0, proizv = 0;
    for(int i= 0; i< n; i++)
    {
      proizv = 1;
      for(int j= 0, k= i; j< n; j++, k= (k==n-1)?0: k+1 )
        proizv *= m[j][k];
      sum += proizv;
    }
    for(int i= 0; i< n; i++)
    {
      proizv= 1;
      for(int j= 0, k= i; j< n; j++, k= (k==0)?n - 1: k-1 )
        proizv *= m[j][k];
      sum -= proizv;
    }
    return sum;
}

int **allocMatrix(int n)
{
      int **m = malloc(sizeof(int *) * n);
      for (int i = 0; i < n; i++)
          m[i] = malloc(sizeof(int) * n);
      return m;
}

void freeMatrix(int n, int **m)
{
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void fillMatrix(int n, int **m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = rand() % 10;
}

void outputMatrix(int n, int **m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

int prime(int n)
{
    int res = 1;
    for (int i = 2; i < n && res; i++)
        if (n % i == 0)
            res = 0;
    return res;
}

void startPipeline(int n, int size)
{
    int tNum = 3;
    pthread_t threads[tNum];
    struct queue data;
    data.fstart = NULL;
    data.fend = NULL;
    data.sstart = NULL;
    data.send = NULL;
    data.tstart = NULL;
    data.tend = NULL;
    data.resstart = NULL;
    data.resend = NULL;
    data.num = n;
    pthread_mutex_init(&(data.m1), NULL);
    pthread_mutex_init(&(data.m2), NULL);
    pthread_mutex_init(&(data.m3), NULL);
    pthread_mutex_init(&(data.resm), NULL);
    pthread_create(&(threads[0]), NULL, startFirst, &data);
    pthread_create(&(threads[1]), NULL, startSecond, &data);
    pthread_create(&(threads[2]), NULL, startThird, &data);

    for (int i = 0; i < n; i++)
    {
        pthread_mutex_lock(&(data.m1));
        firstPush(&data, size);
//        printf("[%d]: Исходные матрицы:\n", i + 1);
//        outputMatrix(data.fend->n, data.fend->m1);
//        printf("\n");
//        outputMatrix(data.fend->n, data.fend->m2);
        pthread_mutex_unlock(&(data.m1));
    }
    data.startTime = tick();

    for (int i = 0; i < tNum; i++)
            pthread_join(threads[i], NULL);

//    for (int i = 0; i < n; i++)
//    {
//        printf("[%d]: Определитель рез. матрицы умножения двух матриц простое число? %d\n", i + 1, data.resstart->res);
//        resPop(&data);
//    }

    FILE *f = fopen("texRes.txt", "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "Tape 1 & Task %d & %d & %d\\\\\n", i + 1, data.fileMatrix[i][0][0], data.fileMatrix[i][0][1]);
        fprintf(f, "Tape 2 & Task %d & %d & %d\\\\\n", i + 1, data.fileMatrix[i][1][0], data.fileMatrix[i][1][1]);
        fprintf(f, "Tape 3 & Task %d & %d & %d\\\\\n", i + 1, data.fileMatrix[i][2][0], data.fileMatrix[i][2][1]);
        fprintf(f, "\\hline\n");
    }
    fclose(f);

    pthread_mutex_destroy(&(data.m1));
    pthread_mutex_destroy(&(data.m2));
    pthread_mutex_destroy(&(data.m3));
    pthread_mutex_destroy(&(data.resm));
}

void startPipelineCalc(int n, int size)
{
    int tNum = 3;
    pthread_t threads[tNum];
    struct queue data;
    data.fstart = NULL;
    data.fend = NULL;
    data.sstart = NULL;
    data.send = NULL;
    data.tstart = NULL;
    data.tend = NULL;
    data.resstart = NULL;
    data.resend = NULL;
    data.num = n;
    pthread_mutex_init(&(data.m1), NULL);
    pthread_mutex_init(&(data.m2), NULL);
    pthread_mutex_init(&(data.m3), NULL);
    pthread_mutex_init(&(data.resm), NULL);
    pthread_create(&(threads[0]), NULL, startFirst, &data);
    pthread_create(&(threads[1]), NULL, startSecond, &data);
    pthread_create(&(threads[2]), NULL, startThird, &data);

    for (int i = 0; i < n; i++)
    {
        pthread_mutex_lock(&(data.m1));
        firstPush(&data, size);
//        printf("[%d]: Исходные матрицы:\n", i + 1);
//        outputMatrix(data.fend->n, data.fend->m1);
//        printf("\n");
//        outputMatrix(data.fend->n, data.fend->m2);
        pthread_mutex_unlock(&(data.m1));
    }
    data.startTime = tick();

    for (int i = 0; i < tNum; i++)
            pthread_join(threads[i], NULL);

//    printf("IM HERE\n");
    int min, max, sum, dif;
    for (int i = 0; i < 3; i++)
    {
//        printf("/");
        min = 100000, max = 0, sum = 0, dif = 0;
        for (int j = 1; j < n; j++)
        {
//            printf("*");
            dif = data.fileMatrix[j][i][0] - data.fileMatrix[j - 1][i][1];
            if (dif < min)
                min = dif;
            if (dif > max)
                max = dif;
            sum += dif;
        }
        printf("[Tape %d]: min %d, max %d, avg %f\n", i, min, max, (float)(sum / n));
    }

//    for (int i = 0; i < n; i++)
//    {
//        printf("[%d]: Определитель рез. матрицы умножения двух матриц простое число? %d\n", i + 1, data.resstart->res);
//        resPop(&data);
//    }

//    FILE *f = fopen("texRes.txt", "w");
//    for (int i = 0; i < n; i++)
//    {
//        fprintf(f, "Tape 1 & Task %d & %d & %d\\\\\n", i + 1, data.fileMatrix[i][0][0], data.fileMatrix[i][0][1]);
//        fprintf(f, "Tape 2 & Task %d & %d & %d\\\\\n", i + 1, data.fileMatrix[i][1][0], data.fileMatrix[i][1][1]);
//        fprintf(f, "Tape 3 & Task %d & %d & %d\\\\\n", i + 1, data.fileMatrix[i][2][0], data.fileMatrix[i][2][1]);
//        fprintf(f, "\\hline\n");
//    }
//    fclose(f);

    pthread_mutex_destroy(&(data.m1));
    pthread_mutex_destroy(&(data.m2));
    pthread_mutex_destroy(&(data.m3));
    pthread_mutex_destroy(&(data.resm));
}

void *startFirst(void *firstData)
{
    struct queue *data = (struct queue *) firstData;
    int done = 0;
    while (1)
    {
        if (done == data->num)
            break;
        pthread_mutex_lock(&(data->m1));
        if (data->fstart == NULL)
        {
            pthread_mutex_unlock(&(data->m1));
            continue;
        }

        data->fileMatrix[done][0][0] = tick() - data->startTime;
        pthread_mutex_unlock(&(data->m1));
        multMatrix(data->fstart->n, data->fstart->m1, data->fstart->m2, data->fstart->res);
        pthread_mutex_lock(&(data->m2));
        data->fileMatrix[done][0][1] = tick() - data->startTime;
        secondPush(data);
        pthread_mutex_unlock(&(data->m2));

        done++;
    }
    return NULL;
}

void *startSecond(void *secondData)
{
    struct queue *data = (struct queue *) secondData;
    int done = 0;
    while (1)
    {
        if (done == data->num)
            break;
        pthread_mutex_lock(&(data->m2));
        if (data->sstart == NULL)
        {
            pthread_mutex_unlock(&(data->m2));
            continue;
        }

        data->fileMatrix[done][1][0] = tick() - data->startTime;
        pthread_mutex_unlock(&(data->m2));
        data->sstart->res = determinator(data->sstart->n, data->sstart->m);
        pthread_mutex_lock(&(data->m3));
        data->fileMatrix[done][1][1] = tick() - data->startTime;
        thirdPush(data);
        pthread_mutex_unlock(&(data->m3));

        done++;
    }
    return NULL;
}

void *startThird(void *thirdData)
{
    struct queue *data = (struct queue *) thirdData;
    int done = 0;
    while (1)
    {
        if (done == data->num)
            break;
        pthread_mutex_lock(&(data->m3));
        if (data->tstart == NULL)
        {
            pthread_mutex_unlock(&(data->m3));
            continue;
        }

        data->fileMatrix[done][2][0] = tick() - data->startTime;
        pthread_mutex_unlock(&(data->m3));
        data->tstart->res = prime(data->tstart->n);
        pthread_mutex_lock(&(data->resm));
        data->fileMatrix[done][2][1] = tick() - data->startTime;
        resPush(data);
        pthread_mutex_unlock(&(data->resm));

        done++;
    }
    return NULL;
}

void firstPush(struct queue *data, int n)
{
    struct flItem *new = malloc(sizeof(struct flItem));
    new->n = n;
    new->m1 = allocMatrix(n);
    fillMatrix(n, new->m1);
    new->m2 = allocMatrix(n);
    fillMatrix(n, new->m2);
    new->res = allocMatrix(n);
    new->next = NULL;
    if (data->fstart == NULL)
    {
        data->fstart = new;
        data->fend = new;
    }
    else
    {
        data->fend->next = new;
        data->fend = new;
    }
}

void firstPop(struct queue *data)
{
    if (data->fstart != data->fend)
    {
        struct flItem *buf = data->fstart;
        data->fstart = buf->next;
        free(buf->m1);
        free(buf->m2);
        free(buf);
    }
    else
    {
        free(data->fstart->m1);
        free(data->fstart->m2);
        free(data->fstart);
        data->fstart = data->fend = NULL;
    }
}

void secondPush(struct queue *data)
{
    struct slItem *new = malloc(sizeof(struct slItem));
    struct flItem *old = data->fstart;
    new->n = old->n;
    new->m = old->res;
    if (data->sstart == NULL)
    {
        data->sstart = new;
        data->send = new;
    }
    else
    {
        data->send->next = new;
        data->send = new;
    }
    firstPop(data);
}

void secondPop(struct queue *data)
{
    if (data->sstart != data->send)
    {
        struct slItem *buf = data->sstart;
        data->sstart = buf->next;
        free(buf->m);
        free(buf);
    }
    else
    {
        free(data->sstart->m);
        free(data->sstart);
        data->sstart = data->send = NULL;
    }
}

void thirdPush(struct queue *data)
{
    struct tlItem *new = malloc(sizeof(struct tlItem));
    struct slItem *old = data->sstart;
    new->n = old->res;
    if (data->tstart == NULL)
    {
        data->tstart = new;
        data->tend = new;
    }
    else
    {
        data->tend->next = new;
        data->tend = new;
    }
    secondPop(data);
}

void thirdPop(struct queue *data)
{
    if (data->tstart != data->tend)
    {
        struct tlItem *buf = data->tstart;
        data->tstart = buf->next;
        free(buf);
    }
    else
    {
        free(data->tstart);
        data->tstart = data->tend = NULL;
    }
}

void resPush(struct queue *data)
{
    struct reslItem *new = malloc(sizeof(struct reslItem));
    struct tlItem *old = data->tstart;
    new->res = old->res;
    if (data->resstart == NULL)
    {
        data->resstart = new;
        data->resend = new;
    }
    else
    {
        data->resend->next = new;
        data->resend = new;
    }
    thirdPop(data);
}

int resPop(struct queue *data)
{
    int res;
    if (data->resstart != data->resend)
    {
        struct reslItem *buf = data->resstart;
        res = buf->res;
        data->resstart = buf->next;
        free(buf);
    }
    else
    {
        res = data->resstart->res;
        free(data->resstart);
        data->resstart = data->resend = NULL;
    }
    return res;
}
