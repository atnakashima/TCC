#ifndef _SAIDA_H
#define _SAIDA_H

#define MAX_LINHA 128
#define carregueGrafo carregueDigrafo

#include "digraph.h"

#define Aresta int

void escrevePrim (Digraph G, Vertex parnt[], int cst[], int custoFGM,
                  char *arquivoSaida, char *nomeArquivo, int arestas);

void escreveKruskal(Edge mst[], int nVertices, int nArestas, int custoFGM,
                    char *arquivoSaida, char *nomeArquivo);

void escreveArborescencia(Digraph G, Vertex parnt[], int cst[],
                          char *arquivoSaida, char *nomeArquivo,
                          char opcao, int raiz);

void escreveGW (Graph F, int custoMinST, char *arquivoSaida,
                char *nomeArquivo);

void carregueTerminal (char *nomeArquivo, Bool *terminal);

Digraph carregueDigrafo (char *nomeArquivo);
#endif
