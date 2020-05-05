/* usado no malloc */
#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "util.h"

#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct
{
    int     first;
    int     last;
    int     validItems;
    Item    *queueFifo;
} circularQueue_t;

typedef struct circularQueue_t *circularQueue;

/*inicializa uma fila de vertices em que casa vertice v tem prioridade cst[v]*/
void pqInit(int);

/*devolve 1 se a fila esta vazia e 0 em caso contrario*/
int pqEmpty();

/*insere o vertice v na fila*/
void pqInsert(Item);

/*retira da fila um vertice de prioridade minima*/
Item pqDelmin(int*);

/*reorganiza a fila depois que o vetor cst[] foi decrementado*/
void pqDec(Item, int[]);

/*libera o espaco*/
void pqFree();

/*retira da fila o primeiro vértice a entrar na fila*/
Item pqGet();

circularQueue_t *queueInit(int maxN);
int queueEmpty(circularQueue_t *theQueue);
int queuePutItem(circularQueue_t *theQueue, Item theItemValue, int maxN);
Vertex queueGetItem(circularQueue_t *theQueue, int maxN);
void queueFree(circularQueue_t *theQueue);

#endif
