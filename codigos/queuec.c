/* usado no malloc */
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

/*------------------------------------------------------
  Implementacao de uma fila CIRCULAR atraves de um vetor.
  http://www.ime.usp.br/~pf/algoritmos/aulas/fila.html
--------------------------------------------------------*/

Item *q;
static int n;
static int inicio, fim;

/* double cst[]; verificar isso - acho que esta errado!*/


/* inicializa uma fila de vertices em que casa vertice v 
   tem prioridade prioridade[v] */
void
pqInit(int maxN, int prioridade[])
{
    n = maxN + 1;
    q = (Item*)malloc(n * sizeof(Item));
    inicio = 0;
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
pqInsert(Item item, int prioridade[])
{
    if ((fim+1)%n == inicio) 
    {
        fprintf("queue.c: A fila transbordou\n");
    }
    q[fim++] = item;
    if (fim == n) fim = 0;
}

/* retira da fila um vertice de prioridade minima*/
Item
pqDelmin(int prioridade[])
{
    int i, j;
    Item x;
    i = inicio;
    for(j = i + 1; j < fim; j++)
        if (prioridade[q[i]] > prioridade[q[j]])
            i = j;
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
