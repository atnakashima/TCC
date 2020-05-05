/* interface para este modulo */
#include "util.h"   /* Bool */
#include <stdio.h>  /* printf() */
#include "goemans-williamson.h"

extern Bool verbose;

static double
custoReduzido(Graph G, Vertex v, link p);


/*-----------------------------------------------------------
  prim(G, s, parnt)

  Recebe um grafo G com custo nos arcos e um um conjunto de vertices
  terminais dados atraves do vetor terminais:

      terminais[v] = TRUE
  se e somente se v e um vertice terminal.

  A função retorna uma árvore obtida pelo algoritmo
  de expansao e um vetor d indexado pelos vertices
  tal que

     d[v] = soma do y_S, v contem S
----------------------------------------------------------------*/

Graph
minSTExpansao(Graph G, int *custoMinSTExp)
{
    Graph  F = NULL;
    int    n = G->V;
    int    custo = 0;

    Vertex v;
    link p;
    int i;
    double epsilon;
    int cstReduzido; /* custo reduzido de uma aresta */

    /* inicialmente F = vazia */
    F = graphInit(n);

    /* inicialmente Lcal = {{v} : v in V_G} */
    ufInit(G->V);

    for (i = 0; i < n-1; i++)
     /*for (i = 0; i < 1; i++) */
    {
	/* encontra a aresta de menor custo reduzido
           entre arestas entre componente da floresta F */

        /* INFINITO = maior custo de uma aresta mais 1 */

	/* Seja epsilon o maior numero tal que y + epsilon respeita c */
        epsilon = INFINITO;
	for (v = 0; v < G->V; v++)
	{
	    for (p = G->adj[v]; p; p = p->next)
	    {
		/* verifique custo reduzido entre aresta com
                   ponto em componentes distintos */
            if (!ufFind(v,p->w))
            {
                if ((cstReduzido = custoReduzido(G, v, p)) < epsilon)
                {
                    epsilon = cstReduzido;
                    /*printf("epsilon = %f\n", epsilon);*/
                }
            }
	    }
	}

	/* y <- y' + epsilon ... */
	for (v = 0; v < G->V; v++)
	{
	    G->d[v] += epsilon;
	    /*printf("d[%d] = %f\n", v, epsilon);*/
	}


	
	/* Defina F' e Lcal' */
	for (v = 0; v < G->V; v++)
	{
	    for (p = G->adj[v]; p; p = p->next)
	    {
		if (!ufFind(v,p->w))
		{
		    /*printf("entrou aqui: %d, %d\n", v, p->w); */
		    if (custoReduzido(G, v, p) == 0)
		    {
			/* Lcal' <- Lcal + V_1 \cup V2 */
			ufUnion(v,p->w);
			custo += p->cst;
			
			/* F' <- F + {v,p->w} */
			graphInsertE(F, v, p->w, p->cst);
		    }
		}
	    }
	}
    }

    ufFree();

    *custoMinSTExp = custo;

    return F;
}


static double
custoReduzido (Graph G, Vertex v, link p)
{
    return p->cst - (G->d[v] + G->d[p->w])/2;
}
