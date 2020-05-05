#ifndef _PRIM_H
#define _PRIM_H

#include "digraph.h"

/*
  Recebe um grafo G com custos nas arestas e calcula uma MST
  da componente de G  que contem o vertice s
  A funcao armazena a MST no vetor parnt,
  tratando-a como uma arborescencia de raiz s
  G eh representado por listas de adjacencia

  A função retorna o custo de uma arvore geradora mínima
*/

int
prim(Graph G, Vertex s, Vertex parnt[], int cst[], Vertex fr[], int *custoFGM);

#endif
