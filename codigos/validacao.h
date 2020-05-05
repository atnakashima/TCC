#ifndef _VALIDACAO_H
#define _VALIDACAO_H
#include "util.h"
#include "digraph.h"

int caminhosOK(Digraph G, Vertex s, Vertex parnt[], int cst[]);

Bool digraphDfsR(Graph T, int lbl[], int cnt);

int dfsR(Graph T, Vertex v, int lbl[], int cnt);

int verificaMst(Graph T, Digraph G);

#endif
