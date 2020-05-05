#ifndef _DIGRAPH_H
#define _DIGRAPH_H
#include "util.h" /* Bool */
#include <limits.h>

#define INFINITO  LONG_MAX


/* Estilo CamelCase */

/* tipos tem a primeira letra maiuscula */
#define Vertex     int
#define Edge       Arc
#define Graph      Digraph

/* nomes de structs */
#define graph      digraph


/* nomes de funções */
#define graphInitSteiner  digraphInitSteiner
#define graphFreeSteiner  digraphFreeSteiner

#define graphInit  digraphInit
#define graphShow  digraphShow
#define graphFree  digraphFree

#define EDGE       ARC

struct arc
{
    Vertex v;
    Vertex w;
    int custo;
};

typedef struct arc Arc;


/*link eh um ponteiro para node*/
typedef struct node *link;

struct node
{
    Vertex w;
    int  cst;
    link next;
};

/*estrutura que representa um digrafo*/
struct digraph
{
    int V;
    int A;
    link   *adj;
    Bool   *terminal; /* so para Steiner */
    double *d; /* so para Steiner */ 
};


/*Digraph contem o endereço de um digraph*/
typedef struct digraph *Digraph;

/*************************custo residual****************************/
/*typedef struct noResidual *pont;

struct noResidual
{
    Vertex u;
    Vertex v;
    int cRes;
    pont next;
};

struct nR
{
    pont *lista;
};

typedef struct nR *custoResidual;
*/
/**************************fim - custo residual****************************/
/*
 * protótipo das funções
 */

/*devolve o endereço de um digrafo com V vertices e nenhum arco*/
Digraph digraphInit(int V);

/*devolve o endereço de um digrafo com V vertices e nenhum arco*/
Digraph digraphInitSteiner(int V);

/*insere um arco v-w no digrafo G*/
void digraphInsertA(Digraph G, Vertex v, Vertex w, int cst);

/*insere uma aresta v-w no grafo G*/
void graphInsertE(Graph G, Vertex v, Vertex w, int cst);

/*remove o arco v-w do digrafo G*/
void digraphRemoveA(Digraph G, Vertex v, Vertex w);

/*remove uma aresta v-w do grafo G*/
void graphRemoveE(Graph G, Vertex v, Vertex w);

/*para cada vertice v, imprime os vertices adjacentes*/
void digraphShow(Digraph G);

/*libera a area alocada por um dado grafo G*/
void digraphFree(Digraph G);

/*libera a area alocada por um dado grafo G*/
void digraphFreeSteiner(Digraph G);

/* verifica se o custo dos caminhos encontrados sao minimos */
int caminhosOK(Digraph G, Vertex s, Vertex parnt[], int cst[]);


/* verificacao de caminhos em arvore geradora */
/*
int digraphDfsR(Graph T, int lbl[], int cnt);
foi para validacao.h
*/

/*
int dfsR(Graph T, Vertex v, int lbl[], int cnt);
foi para validacao.h
*/
#endif
