#include <stdio.h>      /* fopen(), fclose() */
#include <stdlib.h>     /* EXIT_FAILURE */

#include "saida.h"


void
escrevePrim (Digraph G, Vertex parnt[], int cst[], char *arquivoSaida, char *nomeArquivo)
{
    FILE *out;
    Vertex v;

    out = fopen(arquivoSaida, "w");

    if (out == NULL)
    {
        fprintf(stderr,"saida.c: arquivo %s nao pode ser aberto.\n",
                arquivoSaida);
        exit(EXIT_FAILURE);
    }

    fprintf(out, "c Saida referente ao arquivo de entrada < %s >.\n", nomeArquivo);
    fprintf(out, "c Algoritmo utilizado: Algoritmo de Prim\n");

    fprintf(out, "c Nodes = %d\nc Edges = %d\n", G->V, G->V - 1);
    fprintf(out, "q sp %d %d\n", G->V, G->V - 1);
    for(v = 1; v <= G->V; v++)
    {
        if(parnt[v] != v)
        fprintf(out, "E %d %d %d\n", v, parnt[v], cst[v]);
    }
    fclose(out);

}

void
escreveKruskal(Digraph G, Edge mst[], char *arquivoSaida, char *nomeArquivo)
{
    FILE *out;
    Vertex v;

    out = fopen(arquivoSaida, "w");

    if (out == NULL)
    {
        fprintf(stderr,"saida.c: arquivo %s nao pode ser aberto.\n",
                arquivoSaida);
        exit(EXIT_FAILURE);
    }

    fprintf(out, "c Saida referente ao arquivo de entrada < %s >.\n", nomeArquivo);
    fprintf(out, "c Algoritmo utilizado: Algoritmo de Kruskal\n");
    fprintf(out, "c Nodes = %d\nc Edges = %d\n", G->V, G->V - 1);
    fprintf(out, "q sp %d %d\n", G->V, G->V - 1);
    for(v = 0; v < G->V - 1; v++)
    {
        fprintf(out, "E %d %d %d\n", mst[v].w, mst[v].v, mst[v].custo);
    }
    fclose(out);
}

void
escreveArborescencia(Digraph G, Vertex parnt[], int cst[], char *arquivoSaida, char *nomeArquivo, char *alg)
{
    FILE *out;
    Vertex v, w;
    link p;

    out = fopen(arquivoSaida, "w");

    if (out == NULL)
    {
        fprintf(stderr,"saida.c: arquivo %s nao pode ser aberto.\n",
                arquivoSaida);
        exit(EXIT_FAILURE);
    }

    fprintf(out, "c Saida referente ao arquivo de entrada < %s >.\n", nomeArquivo);
    fprintf(out, "c Algoritmo utilizado: Algoritmo de %s\n", alg);
    fprintf(out, "c Nodes = %d\nc Arcs = %d\n", G->V, G->V - 1);
    fprintf(out, "q sp %d %d\n", G->V, G->V - 1);
    for(v = 1; v <= G->V; v++)
    {
        for(p = G->adj[v]; p; p = p->next)
        {
            w = p->w;
            if(parnt[w] == v)
            fprintf(out, "a %d %d %d\n", v, w, p->cst);
        }
    }
    fclose(out);
}



