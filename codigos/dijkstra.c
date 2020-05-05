/* interface deste modulo */
#include "dijkstra.h"
#include <stdio.h> /* printf() */
#include "queue.h" /* pqInit(), pqInsert(), pqEmpty(),... */
#include "util.h"  /* Bool */

extern Bool verbose;

/*------------------------------------------------------------------
  dijkstra(G,s,parnt,cst)

  Recebe um digrafo G com custos nos arcos e um vertice s
  e devolve em parnt a representacao da arborescencia de custo minimo
  com raiz s. Assim, o (reverso) do caminho minimo entre
  s e um vertice v eh

  v, parnt[v], parnt[parnt[v]], parnt[parnt[parnt[v]]], ..., s

  Alem disso a funcao devolve em cst os custos do caminhos minimos
  de s a cada vertice: cst[v] e o custo de um caminho minimo de s a v.

  Pre-condicao: a funcao supoe que o digrafo nao tem arcos de custo
  negativo.

  --------------------------------------------------------------------*/

void
dijkstra(Digraph G, Vertex s, Vertex parnt[], int cst[])
{
    Vertex v, w;
    link p;
    int contador = 0;    /* numero de iterações */

    for (v = 0; v < G->V; v++)
    {
        cst[v] = INFINITO;
        parnt[v] = -1;
    }

    pqInit(G->V);           /* inicializa uma fila de prioridades */

    /* primeiro passo */
    cst[s]   = 0;
    parnt[s] = s;
    pqInsert(s);

    while(!pqEmpty())       /* enquanto a fila de vertices não for vazia */
    {
        v = pqDelmin(cst);  /*retira vertice de prioridade minima*/

        for(p = G->adj[v]; p; p = p->next)
        {
            if(cst[w = p->w] == INFINITO)
            {
                cst[w] = cst[v] + p->cst;
                parnt[w] = v;
                pqInsert(w);
            }

            else if(cst[w] > cst[v] + p->cst)
            {
                cst[w] = cst[v] + p->cst;
                parnt[w] = v;
            }
        }
        contador++;
    }

    if (verbose)
    {
        printf("AVISO: dijkstra.c: Numero de iteracoes: %d\n", contador);
    }

    pqFree();
}


void
dijkstra2(Digraph G, Vertex s, Vertex parnt[], int cst[])
{
    Vertex v, w;
    link p;
    int contador;

    pqInit(G->V);
    contador = 0;
    for(v = 0; v < G->V; v++)
    {
        parnt[v] = -1;
        cst[v] = INFINITO;
        pqInsert(v);
    }

    cst[s] = 0;
    parnt[s] = s;
    pqDec(s, cst);

    while(!pqEmpty())
    {
        v = pqDelmin(cst);
        if(cst[v] == INFINITO)
	    break;

        for(p = G->adj[v]; p; p = p->next)
        {
            w = p->w;
            if(cst[w] > cst[v] + p->cst)
            {
                cst[w] = cst[v] + p->cst;
                parnt[w] = v;
                pqDec(w, cst);
            }
        }
        contador++;
    }

    if (verbose)
    {
        printf("AVISO: dijkstra.c: Numero de iteracoes: %d\n", contador);
    }
    pqFree();
}
