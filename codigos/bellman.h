#ifndef _BELLMAN_H
#define _BELLMAN_H

#define SENTINELA G->V

#include "digraph.h"
#include "queue.h"      /* bellman_ford() */
#include "util.h"       /* Bool, AVISO */
#include <stdio.h>      /* printf() */

/*Encontra o menor caminho de um vertice s a qualquer outro vertice do digrafo*/
/*os custos podem ser negativos*/
void bellmanFord(Digraph G, Vertex s, Vertex parnt[], int cst[]);

/*Encontra o menor caminho de um vertice s a qualquer outro vertice do digrafo*/
/*os custos podem ser negativos*/
void bellmanFord3(Digraph G, Vertex s, Vertex parnt[], int cst[]);
#endif
