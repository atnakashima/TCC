/* interface para este modulo */
#include "bellman.h"

extern Bool verbose;

/*-----------------------------------------------------------
  bellmanFord(G,s,parnt,cst)

  Recebe um digrafo G com custo nos arcos e um vertice s
  e devolve em parnt a representacao da arborescencia de custo minimo
  com raiz s. Assim, o (reverso) do caminho minimo entre
  s e um vertice v eh

   v, parnt[v], parnt[parnt[v]], parnt[parnt[parnt[v]]], ..., s

  Alem disso a funcao devolve em cst os custos do caminhos minimos
  de s a cada vertice: cst[v] e o custo de um caminho minimo de s a v.

  Os custos podem ser negativos.

  Pre-condicao: a funcao supoe que G nao tem um ciclo de custo negativo.

*/


void
bellmanFord(Digraph G, Vertex s, Vertex parnt[], int cst[])
{
    circularQueue_t *theQueue;
    Vertex v, w;
    link p;
    int k = 0;                  /* contador de passos */
    int contador;

    for(v = 0; v <= G->V; v++)
    {
        cst[v]   = INFINITO;
        parnt[v] = -1;
    }
    /* uma posição a mais para a SENTINELA */
    theQueue = queueInit(G->V);           /* inicializa a fila de vértices*/

    /* passo 0 */
    cst[s] = 0;
    parnt[s] = s;
    queuePutItem(theQueue, s, G->V);
    queuePutItem(theQueue, SENTINELA, G->V);
    contador = 0;

    printf("SENTINELA = %d\n", SENTINELA+1);
    while(!queueEmpty(theQueue))
    {
        v = queueGetItem(theQueue, G->V);         /* retiro o primeiro vértice a entrar na fila */
        if (v == -1)
            exit(EXIT_FAILURE);
        printf("queueGet capturou %d\n", (int)v);
        if(v == SENTINELA)
        {
            printf("k = %d\n", k);
            if(k++ == G->V)     /* o número de passos atingiu o número de vértices*/
            {
                if(!queueEmpty(theQueue))  /*verifica ciclo negativo*/
                {
                    AVISO(bellman.c: Ciclo Negativo!);
                    return;
                }
                return;
            }
            queuePutItem(theQueue, SENTINELA, G->V); /* insiro o SENTINELA novamente na fila */
            printf("inseri SENTINELA\n");
        }
        else
        {
            for(p = G->adj[v]; p ; p = p->next)
            {
                /* se eu encontrar um caminho mais barato de v a w */
                if(cst[w = p->w] > cst[v] + p->cst)
                {
                    cst[w] = cst[v] + p->cst;   /* atualizo o custo */
                    parnt[w] = v;               /* armazeno o arco da arborescência */
                    printf("parnt[%d] --> %d\n", w + 1, v + 1);
                    queuePutItem(theQueue, w, G->V);                /* insiro o vértice w na fila */
                    printf("queueInsert: %d\n", w + 1);
                }
            }
        }
        contador++;
    }

    if (verbose)
    {
        printf("AVISO: bellman.c: Numero de iteracoes: %d\n", contador);
    }
/*    queueFree(theQueue);*/               /* libera a memória da fila */
}



void
bellmanFord3(Digraph G, Vertex s, Vertex parnt[], int cst[])
{
    Vertex v, w;
    link p;
    int k;
    Bool mudou;

    /* nessa versao nao temos SENTINELA */
    for(v = 0; v < G->V; v++)
    {
        cst[v]   = INFINITO;
        parnt[v] = -1;
    }

    cst[s]   = 0;
    parnt[s] = s;
    mudou = TRUE;
    for(k = 0; k < G->V && mudou; k++)
    {
       mudou = FALSE;
       for(v = 0; v < G->V; v++)
       {
            p = G->adj[v];
            while (p)
            {
                w = p->w;
                if (cst[w] > cst[v] + p->cst)
                {
                    cst[w] = cst[v] + p->cst;
                    parnt[w] = v;
                    mudou = TRUE;
                }
                p = p->next;

            }
       }
    }

    if (verbose)
    {
        printf("AVISO: bellman.c: Numero de iteracoes = %d\n", k);
    }
    free(p);
}


