
#include "digraph.h"

#ifndef _KRUSKAL_H
#define _KRUSKAL_H

#define maxE 10000000


int kruskal(Graph G, Edge *mst[], int *custoFGM);

void quickSort(Edge a[], int p, int r);

void graphEdges(Graph G, Edge e[]);

Edge retEdge( Vertex v, Vertex w, int cost);

#endif
