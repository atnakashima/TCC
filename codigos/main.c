#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>     /* exit() */
#include <time.h>       /* CLOCKS_PER_SECOND */
#include <string.h>     /* strcmp() */

#include "digraph.h"              /* manipulação de digrafos (grafos) */
#include "bellman.h"              /* algoritmo de Bellman-Ford */
#include "dijkstra.h"             /* algoritmo de Dijkstra */
#include "prim.h"                 /* algoritmo de Prim */
#include "kruskal.h"              /* algoritmo de kruskal */
#include "goemans-williamson.h"   /* algoritmo de Goemans-Williamson */
#include "util.h"                 /* mallocSafe() */
#include "inputlib.h"             /* GetChar() */
#include "io.h"                   /* funcoes de escrita */
#include "validacao.h"            /* funcoes de verificacao de solucao */

/*--------------------------------------------------------------*/
/* MACROS                                                       */

#define DIJKSTRA            'd'
#define BELLMAN_FORD        'b'
#define PRIM                'p'
#define KRUSKAL             'k'
#define GOEMANS_WILLIAMSON  'g'

/*-------------------------------------------------------------*/
/* PROTOTIPOS                                                  */

/* mostra a maneira de usar programa */
static void mostreUso (char *nomeProg);

/* Global. nome do programa */
char *nomeProg;

/* opcao */
Bool  verbose = FALSE;

/*--------------------------main--------------------------------*/
int
main(int argc, char *argv[])
{
    Digraph G;              /* (di)grafo de entrada  */
    Digraph T;              /* arvore geradora (Kruskal e Prim) */

    char algoritmo = '\0';  /* metodo de resolucao */
    int *custo = NULL;      /* custo dos arcos */
    int *parnt = NULL;      /* vetor de ponteiros para pais */
    clock_t t;              /* medição do tempo de execução do algoritmo */

    /*-------------------opcoes default------------------------------*/
    /* opcoes de execucao e seus valores default */
    int    arg;

    /* raiz da arborescencia */
    /* no problema proposto em DIMACS a contagem dos vértices inicia-se
       em 1 enquanto no programa, iniciaremos com o vertice zero */
    Vertex raiz = 0;

    /* arquivo no formato stp com o grafo */
    char *arqEntrada = NULL;

    /* arquivo no formato com uma arvore ou caminho */
    char *arqSaida   = NULL;

    nomeProg = argv[0];

    /*----------------fim das configuracoes default------------------*/

    /* 1 pegue as opcoes da linha de comando */

    if (argc < 2)
    {
        mostreUso(nomeProg);
        return EXIT_SUCCESS;
    }

    for (arg = 1; arg < argc; arg++)
    {
        if (!strncmp(argv[arg], "-h", 2))
        {
            mostreUso(nomeProg);
            return EXIT_SUCCESS;
        }
        else if (!strncmp(argv[arg], "-d", 2)) algoritmo  = DIJKSTRA;
        else if (!strncmp(argv[arg], "-b", 2)) algoritmo  = BELLMAN_FORD;
        else if (!strncmp(argv[arg], "-k", 2)) algoritmo  = KRUSKAL;
        else if (!strncmp(argv[arg], "-p", 2)) algoritmo  = PRIM;
        else if (!strncmp(argv[arg], "-g", 2)) algoritmo  = GOEMANS_WILLIAMSON;
        else if (!strncmp(argv[arg], "-v", 2)) verbose    = TRUE;
        else if (!strncmp(argv[arg], "-r", 2)) raiz       = atoi(argv[++arg])-1;
        else if (!strncmp(argv[arg], "-e", 2))
        {
            /* nome do arquivo com o grafo */
            arqEntrada = argv[++arg];
        }
        else if (!strncmp(argv[arg], "-s", 2))
        {
            /* nome do arquivo com o grafo */
            arqSaida   = argv[++arg];
        }

        else
        {
            /* opcao invalida */
            fprintf(stderr, "%s: opcao invalida '%s'\n", nomeProg, argv[argc]);
            mostreUso(nomeProg);
            return EXIT_FAILURE;
        }
    }

    /* nenhum metodo foi escolhido */
    if (algoritmo == '\0')
    {
        fprintf(stderr, "%s: opcao invalida '%s'\n", nomeProg, argv[argc]);
        mostreUso(nomeProg);
        return EXIT_FAILURE;
    }

    /* nao passou o arquivo de entrada */
    if (arqEntrada == NULL)
    {
        printf("AVISO: main.c: O arquivo de entrada nao foi definido\n"
               "       Digite aqui o nome/caminho do/para o arquivo de entrada\n");
        /* entrada pelo teclado */
        arqEntrada = getString();
    }

    /* nao passou o arquivo de saida */
    if (arqSaida == NULL)
    {
        printf("AVISO: main.c: O arquivo de saida nao foi definido\n"
               "       Digite aqui o nome/caminho do/para o arquivo de saida\n");
        /* entrada pelo teclado */
        arqSaida = getString();
    }

    AVISO(main.c: prestes a carregar o digrafo.);
    G = carregueDigrafo(arqEntrada);
    if (verbose)
    {
        printf("AVISO: main.c: carreguei o digrafo: %d vertices, %d arcos.\n",
	       G->V, G->A);
    }

#ifdef MOSTRE_DIGRAFO
    digraphShow(G);
#endif

    /* aloco uma posicao a mais para a SENTINELA */
    if (!(custo = mallocSafe((G->V + 1) * sizeof(int))))
    {
        /* Erro */
        fprintf(stderr,
                "ERRO : main.c: nao consegui alocar vetor 'custo' (%d).\n",
                G->V);

        /* libera memoria */
        digraphFree(G);
        /* tchau */
        return EXIT_FAILURE;
    }

    /* aloco uma posicao a mais para a SENTINELA */
    if (!(parnt = mallocSafe((G->V + 1) * sizeof(int))))
    {
        fprintf(stderr,
                "ERRO : main.c: nao consegui alocar vetor 'parnt' (%d).\n",
                G->V);
        digraphFree(G);
        return EXIT_FAILURE;
    }

    t = clock();        /* inicio da contagem de tempo */

    switch(algoritmo)
    {

	/*---------------------Dijkstra----------------------*/
    case DIJKSTRA:
 	/*-------------------Bellman_Ford--------------------*/
    case BELLMAN_FORD:
    {

	if (verbose)
	{
	    printf("PRINT: main.c: algoritmo: %s escolhido\n",
		   algoritmo == DIJKSTRA? "Dijkstra": "Bellman-Ford");
	}

        /*dijkstra2(G, raiz, parnt, custo);*/
	if (algoritmo == DIJKSTRA)
	{
	    /*---------------------Dijkstra----------------------*/
	    dijkstra(G, raiz, parnt, custo);
	}
	else
	{
	    /*-------------------Bellman_Ford---------------------*/
	    bellmanFord(G, raiz, parnt, custo);
	}

        AVISO(main.c Verificando caminhos encontrados...);
        if (caminhosOK(G, raiz, parnt, custo))
        {
            AVISO(main.c: caminho encontrado e minimo);
        }
        else
        {
            ERRO(main.c: caminho encontrado nao e minimo);
        }
        AVISO(main.c: Escrevendo arquivo de saida);
        escreveArborescencia(G, parnt, custo, arqSaida, arqEntrada, algoritmo, raiz);
        AVISO(main.c: Fim da escrita do arquivo de saida);

        break;
    }


    /*------------------------Prim------------------------*/
    case PRIM:
    {
        Vertex *fr = NULL;   /* franja do algoritmo de prim */
        int custoFGM;
	    int arestas;

	    AVISO(main.c: algoritmo: Algoritmo de Prim escolhido);

	    /* franja para o algoritmo de prim */
	    if (!(fr = mallocSafe((G->A) * sizeof(int))))
	    {
		fprintf(stderr,"PRINT: main.c: nao consegui alocar vetor 'fr' (%d)\n",
			G->V);
		digraphFree(G);
		return EXIT_FAILURE;
	    }

	    arestas = prim(G, raiz, parnt, custo, fr, &custoFGM);

	    AVISO(main.c: Escrevendo arquivo de saida);
	    escrevePrim(G, parnt, custo, custoFGM, arqSaida, arqEntrada, arestas);
	    AVISO(main.c: Fim da escrita do arquivo de saida);

	    T = carregueDigrafo(arqSaida);

	    verificaMst(T, G);

	    free(fr);
	    digraphFree(T);
	    break;
    }

    /*-----------------------Kruskal----------------------*/
    case KRUSKAL:
    {
        Edge *mst = NULL;
        int custoFGM;
        int nArestas;

        AVISO(main.c: Algoritmo de Kruskal escolhido);

        AVISO(kruskal: alocando memoria arestas da FGM);
        if (!(mst = mallocSafe((G->V) * sizeof(Edge))))
        {
            fprintf(stderr,"PRINT: main.c: nao consegui alocar vetor 'mst' (%d).\n",
                    G->V);
            digraphFree(G);
            return EXIT_FAILURE;
        }

        nArestas =  kruskal(G, &mst, &custoFGM);

        AVISO(main.c: Escrevendo arquivo de saida);
        escreveKruskal(mst, G->V, nArestas, custoFGM, arqSaida, arqEntrada);
        AVISO(main.c: Fim da escrita do arquivo de saida);

        T = carregueDigrafo(arqSaida);
        verificaMst(T, G);

        free(mst);
        digraphFree(T);
        break;
    }

    /*--------------------GOEMANS-WILLIAMSON----------------------*/
    case GOEMANS_WILLIAMSON:
    {
	Graph F;
	int custoMinSTExp;
	
	AVISO(main.c: algoritmo de Goemans-Williamson);
	AVISO(maim.c: alocando memoria arestas para vetor de terminais);
	
        F = minSTExpansao(G, &custoMinSTExp);
        escreveGW (F, custoMinSTExp, arqSaida, arqEntrada);
	
        graphFree(F);
        break;
    }

    default:
    {
        ERRO(main.c: algoritmo invalido!\n);
        break;
    }

    } /* switch end */

    /* consumo de tempo */
    t = clock() - t;
    printf ("oticomb: Solucao encontrada em %f segundos.\n",
            (float)t/CLOCKS_PER_SEC);

    if (!verbose) printf("\n\n");

    /* libere memoria alocada */
    free(custo);
    free(parnt);
    algoritmo == GOEMANS_WILLIAMSON? digraphFreeSteiner(G): digraphFree(G);

    return 0;
}


/* mostra a maneira de usar programa */
static void
mostreUso (char *nomeProg)
{
    printf("prompt> ./oticomb [-v] [-d|-b|-p|-k|-g] [-r raiz]\n"
           "                  [-e \"arq grafo entrada\"]\n"
           "                  [-s \"arq grafo saida\"]\n"
           "        -v = verboso\n"
           "        -d = algoritmo de Dijkstra\n"
           "        -b = algoritmo de Bellman-Ford\n"
           "        -p = algoritmo de Prim\n"
           "        -k = algoritmo de Kruskal\n"
           "        -g = algoritmo de Goemans-Williamson\n"
           "        -r raiz = raiz para Dijkstra, Bellman-Ford e Prim\n"
           "        -e entrada = arquivo com o di(grafo) de entrada\n"
           "        -s saida   = arquivo com o di(grafo) de saida\n");
}
