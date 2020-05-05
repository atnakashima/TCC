/* interface para este modulo */
#include "digraph.h"

#include <stdio.h>
#include <stdlib.h>

/* Estilo CamelCase */
#include "queue.h"
#include "util.h"

extern Bool verbose;

/* Recebe um vertice w e um endereco para um nó(next).
   Devolve o endereco de um novo no xcom x.w = w e x.next = next*/
link
NEW(Vertex w, int cst, link next)
{
    link p    = malloc(sizeof *p);
    p->w      = w;
    p->cst    = cst;
    p->next   = next;
    return p;
}


/* Devolve o endereço de um digrafo com V vertices e nenhum arco*/
Digraph
digraphInit (int V)
{
    Vertex v;
    Digraph G = malloc(sizeof *G);

    G->V        = V;
    G->A        = 0;
    G->terminal = NULL;

    G->adj      = malloc(V * sizeof(link));

    for(v = 0; v < V; v++)
    {
        G->adj[v] = NULL;
    }

    return G;
}

/* Devolve o endereço de um digrafo com V vertices e nenhum arco*/
Digraph
digraphInitSteiner (int V)
{
    Vertex v;
    Digraph G = malloc(sizeof *G);

    G->V = V;
    G->A = 0;

    G->adj      = malloc(V * sizeof(link));
    G->terminal = malloc(V * sizeof(Bool));
    G->d        = malloc(V * sizeof(double));

    for(v = 0; v < V; v++)
    {
        G->adj[v]      = NULL;
	G->terminal[v] = FALSE;
        G->d[v]        = 0;
    }

    return G;
}


/* Insere um arco v-w no digrafo G*/
void
digraphInsertA (Digraph G, Vertex v, Vertex w, int cst)
{
    link p;
    if (v == w) return;
    for (p = G->adj[v]; p != NULL; p = p->next)
    {
        if (p->w == w)
	    return;
    }

    G->adj[v] = NEW(w, cst, G->adj[v]);
    G->A++;
}

/*insere uma aresta v-w no grafo G*/
void
graphInsertE(Graph G, Vertex v, Vertex w, int cst)
{
    digraphInsertA(G, v, w, cst);
    digraphInsertA(G, w, v, cst);
}

/*remove o arco v-w do digrafo G*/
void
digraphRemoveA(Digraph G, Vertex v, Vertex w)
{
    link p, aux, ant;

    aux = NULL;

    /*não existe aresta se os vertices inicial e final são iguais*/
    if (v == w)
        return;

    ant = G->adj[v];

    /*se não há arestas associadas, não faz nada*/
    if(ant == NULL)
        return;

    /*caso w esteja na primeira posição, eu analiso separado*/
    if (ant->w == w)
    {
        aux = ant;
        G->adj[v] = ant->next;
    }

    /*demais casos*/
    else
    {
        for(p = ant->next; p ; p = p->next)
        {
            if(p->w == w)
            {
                aux = p;
                ant->next = p->next;
                break;
            }
            ant = ant->next;
        }
    }
    free(aux);
    G->A--;
}

/*remove a aresta v-w do grafo G*/
void
graphRemoveE(Graph G, Vertex v, Vertex w)
{
    digraphRemoveA(G, v, w);
    digraphRemoveA(G, w, v);
}

/*para cada vertice v, imprime os vertices adjacentes*/
void
digraphShow(Digraph G)
{
    Vertex v;
    link p;
    AVISO(digraph.c: O digrafo eh:);
    for(v = 0; v < G->V; v++)
    {
        printf("%2d ",v);
        for(p = G->adj[v]; p != NULL; p = p->next)
            printf("%2d: %8d;     ", p->w, p->cst);
        printf("\n");
    }
}

/*libera a area alocada por um dado grafo G*/
void
digraphFree(Digraph G)
{
    Vertex v;
    link p;
    link q;

    AVISO(digraph.c: Liberando a memoria do digrafo);
    for(v = 0; v < G->V ; v++)
    {
        for(p = G->adj[v]; p; p = q)
        {
            q = p->next;
            free(p);
        }
    }
    free(G->adj);
    free(G);
    AVISO(digraph.c: Memoria liberada);
}

/*libera a area alocada por um dado grafo G*/
void
digraphFreeSteiner(Digraph G)
{
    Vertex v;
    link p;
    link q;

    AVISO(digraph.c: Liberando a memoria do digrafo);
    for(v = 0; v < G->V ; v++)
    {
        for(p = G->adj[v]; p; p = q)
        {
            q = p->next;
            free(p);
        }
    }

    free(G->adj);
    free(G->terminal);
    free(G->d);
    free(G);
    AVISO(digraph.c: Memoria liberada);
}



