#include "queue.h"

/*------------------------------------------------------
  Implementacao de uma fila atraves de um vetor.
  http://www.ime.usp.br/~pf/algoritmos/aulas/fila.html
--------------------------------------------------------*/

static Item *q;
static const int inicio = 0;
static       int fim;

/***********************/
/* filas de prioridade */
/***********************/

/* inicializa uma fila de vertices em que casa vertice v
   tem prioridade prioridade[v] */
void
pqInit(int maxN)
{
    q = (Item*) malloc(maxN*sizeof(Item));
    fim = 0;
}

/*devolve 1 se a fila esta vazia e 0 em caso contrario*/
int
pqEmpty()
{
    return inicio == fim;
}

/*insere o vertice v na fila*/
void
pqInsert(Item item)
{
    int i;

    for (i = inicio; i < fim; i++)
    {
        if (q[i] == item)  return;
    }

    q[fim++] = item;
}

/* retira da fila um vertice de prioridade minima*/
Item
pqGet()
{
    int i, j;
    Item x;
    i = inicio;
    x = q[i];
    for (j = i + 1; j < fim; j++)
    {
        q[j - 1] = q[j];
    }
    /*x = q[i];
    q[i] = q[--fim];*/
    fim--;
    return x;
}


/* retira da fila um vertice de prioridade minima*/
Item
pqDelmin(int prioridade[])
{
    int i, j;
    Item x;
    i = inicio;
    for (j = i + 1; j < fim; j++)
    {
        if (prioridade[q[i]] > prioridade[q[j]])
            i = j;
    }
    x = q[i];
    q[i] = q[--fim];

    return x;
}

/*reorganiza a fila depois que o vetor cst[] foi decrementado*/
void
pqDec(Vertex v, int prioridade[])
{
    /*nada(!?)*/
}

/*libera o espaco*/
void
pqFree()
{
    free(q);
}

/*************/
/* fila FIFO */
/*************/

circularQueue_t *queueInit (int maxN)
{
    circularQueue_t *theQueue;
    theQueue = mallocSafe (sizeof (circularQueue_t));
    theQueue->validItems  =  0;
    theQueue->first       =  0;
    theQueue->last        =  0;
    theQueue->queueFifo   = (Item*) malloc((maxN + 1) * sizeof(Item));
    return theQueue;
}

/* retorna 1 se a fila esta vazia e 0 em caso contrário */
int queueEmpty (circularQueue_t *theQueue)
{
    if(theQueue->validItems==0)
        return(1);
    else
        return(0);
}

/* verifica se há espaço na fila */
/* se houver, adiciona o elemento no final da fila */
int queuePutItem(circularQueue_t *theQueue, Item theItemValue, int maxN)
{
    if(theQueue->last > (maxN + 1))
    {
        printf("Reach the queue's end\n");
        theQueue->last = 0;
        theQueue->queueFifo[theQueue->last] = theItemValue;
        theQueue->last++;
    }

    else
    {
        printf("Insert Item in the queue\n");
        theQueue->queueFifo[theQueue->last] = theItemValue;
        theQueue->last++;
    }
    theQueue->validItems++;
    return(0);
}

/* retorna -1 se fila é vazia, caso contrario retira o primeiro elemento */
Vertex queueGetItem(circularQueue_t *theQueue, int maxN)
{
    Item aux;
    if(queueEmpty(theQueue))
    {
        printf("isempty\n");
        return (Vertex)(-1);
    }

    else
    {
        printf("Get Item from the queue\n");
        aux=theQueue->queueFifo[theQueue->first];
        if ((theQueue->first+1) > (maxN + 1))
            theQueue->first = 0;
        else
            theQueue->first++;
        theQueue->validItems = theQueue->validItems - 1;
        return (Vertex) aux;
    }
}

void queueFree(circularQueue_t *theQueue)
{
    free(theQueue->queueFifo);
/*    free(circularQueue_t);*/
}
