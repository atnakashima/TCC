#include <stdio.h>      /* fopen(), fclose() */
#include <stdlib.h>     /* EXIT_FAILURE */

#include "io.h"
#include "util.h"
#include "digraph.h"

extern Bool verbose;

void
escrevePrim (Digraph G, Vertex parnt[], int cst[], int custoFGM,
             char *arquivoSaida, char *nomeArquivo, int arestas)
{
    FILE *out;
    Vertex v;

    out = fopen(arquivoSaida, "w");

    if (out == NULL)
    {
        fprintf(stderr,"PRINT: io.c: arquivo %s nao pode ser aberto.\n",
                arquivoSaida);
        exit(EXIT_FAILURE);
    }

    fprintf(out, "c Saida referente ao arquivo de entrada < %s >.\n",
            nomeArquivo);
    fprintf(out, "c Algoritmo de Prim\n");
    fprintf(out, "c Custo floresta geradora = %d\n", custoFGM);
    fprintf(out, "c Nodes = %d\nc Edges = %d\n", G->V, arestas);
    fprintf(out, "c Numero de compontes conexas = %d\n", G->V - arestas);

    fprintf(out, "q sp %d %d\n", G->V, arestas);

    for(v = 0; v < G->V; v++)
    {
        if (parnt[v] != v)
        {
            fprintf(out, "E %d %d %d\n", v + 1, parnt[v] + 1, cst[v]);
        }
    }
    fclose(out);
}

void
escreveKruskal(Edge mst[], int nVertices, int nArestas, int custoFGM,
	       char *arquivoSaida, char *nomeArquivo)
{
    FILE *out;
    Aresta e;

    out = fopen(arquivoSaida, "w");

    if (out == NULL)
    {
        fprintf(stderr,"ERRO : io.c: arquivo %s nao pode ser aberto.\n",
                arquivoSaida);
        exit(EXIT_FAILURE);
    }

    fprintf(out, "c Saida referente ao arquivo de entrada < %s >.\n",
            nomeArquivo);
    fprintf(out, "c Algoritmo de Kruskal\n");
    fprintf(out, "c Custo da FGM = %d\n", custoFGM);
    fprintf(out, "c Nodes = %d\nc Edges = %d\n", nVertices, nArestas);
    fprintf(out, "c Numero de compontes conexas = %d\n", nVertices-nArestas);
    fprintf(out, "q sp %d %d\n", nVertices, nArestas);

    for(e = 0; e < nArestas; e++)
    {
        fprintf(out, "E %d %d %d\n", mst[e].w + 1, mst[e].v + 1, mst[e].custo);
    }
    fclose(out);
}

void
escreveArborescencia (Digraph G, Vertex parnt[], int cst[],
                      char *arquivoSaida, char *nomeArquivo,
                      char opcao, int raiz)
{
    FILE *out;
    Vertex v, w;
    link p;

    out = fopen(arquivoSaida, "w");

    if (out == NULL)
    {
        fprintf(stderr,"PRINT: io.c: arquivo %s nao pode ser aberto.\n",
                arquivoSaida);
        exit(EXIT_FAILURE);
    }

    fprintf(out, "c Saida referente ao arquivo de entrada < %s >.\n", nomeArquivo);
    fprintf(out, "c Algoritmo utilizado: Algoritmo de %s\n", opcao == 'd'? "Dijkstra": "Bellman-Ford" );
    fprintf(out, "c Raiz da arborescência: %d\n", raiz + 1);
    fprintf(out, "c Nodes = %d\nc Arcs = %d\n", G->V, G->V - 1);
    fprintf(out, "p sp %d %d\n", G->V, G->V - 1);
    for(v = 0; v < G->V; v++)
    {
        for(p = G->adj[v]; p; p = p->next)
        {
            w = p->w;
            if(parnt[w] == v)
                fprintf(out, "a %d %d %d\n", v + 1, w + 1, p->cst);
        }
    }
    fclose(out);
}

/*----------------------------------------------------------------*/
Digraph
carregueDigrafo (char *nomeArquivo)
{
    Digraph G = NULL;

    FILE *in;

    char linha[MAX_LINHA];

    Vertex   u;
    Vertex   v;
    int cst;

    int n = -1;      /* numero de vertices */
    int m = -1;      /* numero de arcos */
    int nLin = 0;    /* numero da linha do arquivo */

    in = fopen(nomeArquivo, "r");

    if (in == NULL)
    {
        fprintf(stderr,"PRINT: io.c: arquivo %s nao pode ser aberto.\n",
                 nomeArquivo);
        exit(EXIT_FAILURE);
    }

    while (!feof(in))
    {
        fgets(linha, MAX_LINHA, in);
        nLin++;
        switch(linha[0])
        {

	/* comentario */
        case 'c':
        case 'D':
        {
            break;
        }
	
        /* problema, um digrafo ou grafo deve ser criado */
        case 'p':  /* problema, digrafo */
        case 'q':  /* problema, grafo */
        case 's':  /* problema de Steiner, grafo com terminal, d */
            /* +4 pula 'p sp' */
        {
            if (sscanf(linha + 4,"%d %d", &n, &m) != 2)
            {
                ERRO(io.c: linha do problema com formato errado);
                fclose(in);
                exit(EXIT_FAILURE);
            }
	    
            /* cria a estrutura de um digrafo/grafo vazio */
            G = linha[0] == 'p'? digraphInit(n):
		linha[0] == 'q'? graphInit(n): graphInitSteiner(n);
	    
	    if (verbose)
	    {
		printf("AVISO: io.c: estrutura digraph/graph com "
		       "%d vertices criada\n", n);
	    }
            break;
        }
	
        case 'T': /* terminal */
	{
	    int t;
	    
	    if (G == NULL)
            {
                ERRO(io.c: digrafo precisa ser criado antes de inserir terminal);
                fclose(in);
                exit(EXIT_FAILURE);
            }

	    sscanf(linha + 1, "%d", &t);
	    G->terminal[t] = TRUE;
	    break;
	}
	
        case 'a': /* arco */
	{
            if (G == NULL)
            {
                ERRO(io.c: digrafo precisa ser criado antes de inserir arco);
                fclose(in);
                exit(EXIT_FAILURE);
            }
	    
            if (sscanf(linha + 1,"%d %d %d", &u, &v, &cst) != 3)
            {
                fprintf(stderr,
                        "ERRO: io.c: problema na linha %d de um arco\n",
			linha[0], nLin);
                fclose(in);
                digraphFree(G);
                exit(EXIT_FAILURE);
            }
	    
            digraphInsertA(G, u - 1, v - 1, cst);
            break;
	}
	
	case 'E': /* aresta */
	{
            if (G == NULL)
            {
                ERRO(io.c: grafo precisa ser criado antes de inserir aresta);
                fclose(in);
                exit(EXIT_FAILURE);
            }
	    
            if (sscanf(linha + 1,"%d %d %d", &u, &v, &cst) != 3)
            {
                fprintf(stderr,
                        "io.c: problema na linha %d de uma aresta\n", nLin);
                fclose(in);
                digraphFree(G);
                exit(EXIT_FAILURE);
            }
	    
            graphInsertE(G, u - 1, v - 1, cst);
	    break;

	}
	
        default:
            printf("ERRO : io.c: caractere no inicio da linha '%c' (%d)\n",
                   linha[0], linha[0]);
            break;
        }
    }

    fclose(in);

    return G;
}


void
escreveGW (Graph F, int custoMinST, char *arquivoSaida, char *nomeArquivo)
{
    FILE *out;
    Vertex v;
    link p;

    out = fopen(arquivoSaida, "w");

    if (out == NULL)
    {
        fprintf(stderr,"PRINT: io.c: arquivo %s nao pode ser aberto.\n",
                arquivoSaida);
        exit(EXIT_FAILURE);
    }

    fprintf(out, "c Saida referente ao arquivo de entrada < %s >.\n",
            nomeArquivo);
    fprintf(out, "c Algoritmo de Goemans-Williamson\n");
    fprintf(out, "c Custo da árvore geradora = %d\n", custoMinST);
    fprintf(out, "c Nodes = %d\nc Edges = %d\n", F->V, F->A/2);

    fprintf(out, "q sp %d %d\n", F->V, F->A/2);

    for(v = 0; v < F->V; v++)
    {
        for(p = F->adj[v]; p; p = p->next)
        {
	    if (v < p->w)
	    {
		fprintf(out, "E %d %d %d\n", v + 1, p->w + 1, p->cst);
	    }
        }
    }
    fclose(out);
}
