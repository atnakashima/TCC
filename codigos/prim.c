/* interface para este modulo */
#include "prim.h"
#include "queue.h"  /*graphMstP2*/
#include "util.h"   /* Bool */
#include <stdio.h>  /* printf() */

extern Bool verbose;

/*-----------------------------------------------------------
  prim(G, s, parnt, cst, fr)

  Recebe um grafo G com custo nos arcos e um vertice s
  e devolve em parnt o FGM com raiz s.

  Alem disso a funcao devolve em cst os custos das arestas
  que compõe a FGM.

  Os custos podem ser negativos.
*/

int
prim(Graph G, Vertex s, Vertex parnt[], int cst[], Vertex fr[], int *custoFGM)
{
    Vertex v, w;
    link p;
    int contador = 0;
    int custo    = 0;
    int arestas  = 0;

    for(v = 0; v < G->V; v++)
    {
        cst[v] = INFINITO;
        parnt[v] = -1;
    }

    pqInit(G->V);
    cst[s] = 0;
    fr[s]  = s;
    pqInsert(s);

    while(!pqEmpty())
    {
        v = pqDelmin(cst);
        parnt[v] = fr[v];
        for(p = G->adj[v]; p; p = p->next)
        {
            w = p->w;
            if(parnt[w] == -1)
            {
                if(cst[w] == INFINITO)
                {
                    cst[w] = p->cst;
                    fr[w] = v;
                    pqInsert(w);
                }
                else if(cst[w] > p->cst)
                {
                    cst[w] = p->cst;
                    fr[w] = v;
                    pqDec(w, cst);
                }
            }
        }

        contador++;
    }

    for (v = 0; v < G->V; v++)
    {
        if (cst[v] != INFINITO)
        {
            custo += cst[v];
        }
        if (parnt[v] != v && parnt[v] != -1)
        {
            arestas++;
        }
    }

    if (verbose)
    {
        printf("AVISO: prim.c: Numero de iteracoes: %d\n", contador);
    }
    pqFree();

    *custoFGM = custo;

    return arestas;
}
