#ifndef _SAIDA_H
#define _SAIDA_H

#include "digraph.h"



void escrevePrim (Digraph G, Vertex parnt[], int cst[], char *arquivoSaida, char *nomeArquivo);

void escreveKruskal(Digraph G, Edge mst[], char *arquivoSaida, char *nomeArquivo);

void escreveArborescencia(Digraph G, Vertex parnt[], int cst[], char *arquivoSaida, char *nomeArquivo, char *alg);


#endif
