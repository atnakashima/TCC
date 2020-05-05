#include "digraph.h"


#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

/* encontra uma arvore de caminhos minimos com raiz em s */
void dijkstra(Digraph G, Vertex s, Vertex parnt[], int cst[]);

void dijkstra2(Digraph G, Vertex s, Vertex parnt[], int cst[]);

#endif
