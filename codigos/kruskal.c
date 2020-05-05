#include <stdio.h>

/* interface para este modulo */
#include "kruskal.h"
#include "util.h" /* Bool, mallocSafe() */
#include "union.h"

extern Bool verbose;

static int
separa (Edge v[], int p, int r);


/*-----------------------------------------------------------
  kruskal(G, &mst)

  Recebe um grafo G com custo nos arcos e um vertice s
  e devolve em parnt a FGM para o grafo G

  A funcao armazena em mst as arestas que compõe a FGM
  mst eh um vetor de Edges

  Os custos podem ser negativos.
*/


int
kruskal(Graph G, Edge *mst[], int *custoFGM)
{
    int i, k, E;
    Edge *a;
    int custo = 0;

    E = G->A/2;

    AVISO(kruskal.c: alocando memoria para as arestas);
    a    = mallocSafe(E * sizeof(Edge));
    if (verbose)
        printf("AVISO: kruskal.c: %d x %ld = %ld bytes alocados\n",
                E, sizeof(Edge), E * sizeof(Edge) );

    AVISO(kruskal.c: copiando aresta para vetor);
    graphEdges(G, a);
    AVISO(kruskal.c: arestas copiadas);

    AVISO(kruskal.c: ordenando arestas);
    quickSort(a, 0, E-1);
    AVISO(kruskal.c: arestas ordenadas);

    AVISO(kruskal.c: criando componentes unitarios);
    ufInit(G->V);
    AVISO(kruskal.c: componentes unitarios criados);

    AVISO(kruskal.c: construindo FGM);
    for(i = k = 0; i < E && k < G->V - 1; i++)
    {
        if(!ufFind(a[i].v, a[i].w))
        {
            ufUnion(a[i].v, a[i].w);
            (*mst)[k++] = a[i];
            custo += a[i].custo;
        }
    }

    
    AVISO(kruskal.c: FGM construida);
    
    if (verbose)
        printf("AVISO: kruskal.c: custo da FGM = %d\n", custo);

    AVISO(kruskal.c: liberando memoria alocada para union-find);
    ufFree();
    AVISO(kruskal.c: memoria liberada);

    AVISO(kruskal.c: liberando memoria alocada para as arestas);
    free(a);
    AVISO(kruskal.c: memoria liberada);

    *custoFGM = custo;

    return k;
}


void
quickSort(Edge a[], int p, int r)
{
    int j;
    while (p < r)
    {
        j = separa(a, p, r);
        if (j - p < r - j)
        {
            quickSort(a, p, j-1);
            p = j + 1;
        }
        else
        {
            quickSort(a, j + 1, r);
            r = j - 1;
        }
    }
}


static int
separa(Edge v[], int p, int r)
{
    int c, i, j;
    Arc t, t1;
    c  = v[p].custo;
    t1 = v[p];


    i = p+1;
    j = r;

    while (1)
    {
        while (i <= r && v[i].custo <= c)
            ++i;
        while (c < v[j].custo)
            --j;
        if (i >= j)
            break;

	t = v[i];
	v[i] = v[j];
	v[j] = t;
	++i; --j;
    }
    v[p] = v[j], v[j] = t1;
    return j;
}


void
graphEdges(Graph G, Edge e[])
{
    int i = 0;
    link a;
    Vertex v;

    for (v = 0; v < G->V; ++v)
    {
        for (a = G->adj[v]; a; a = a->next)
        {
            if (v < a->w)
            {
                e[i++] = retEdge(v, a->w, a->cst);
            }
        }
    }
}



Edge
retEdge( Vertex v, Vertex w, int cost)
{
    Edge e;
    e.v = v;
    e.w = w;
    e.custo = cost;
    return e;
}

