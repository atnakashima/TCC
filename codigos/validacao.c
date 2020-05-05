#include "validacao.h"
#include "util.h"       /* macros ERRO e AVISO */
#include <stdio.h>      /* stderr */

extern Bool verbose;

/* usado na verificacao da arvore geradora minima */
static int cnt, *lbl;

int
caminhosOK(Digraph G, Vertex s, Vertex parnt[], int cst[])
{
    Vertex v, w;
    link p;
    int ok;
    ok = TRUE;

    if (cst[s] != 0)
    {
        fprintf(stderr,"ERRO: validacao.c: custo da raiz %d nao eh zero=%d\n",
                s, cst[s]);
        ok = FALSE;
    }

    /* verifique se cst e um c-pontencial */
    for (v = 0; v < G->V; v++)
    {
        for(p = G->adj[v]; p != NULL; p = p->next)
        {
            /* a diferenca de potencial entre v e w deve ser menor que o
               custo do arco vw = p->cst */
            if (cst[w = p->w] - cst[v] > p->cst)
            {
                fprintf(stderr,
                        "ERRO: validacao.c: arco %d-%d nao satisfaz diferenca de potencia\n"
                        "      cst[%d] - cst[%d] = %d - %d > %d == c[%d-%d]\n",
                        v + 1, w + 1, w + 1, v + 1, cst[w], cst[v], p->cst, v + 1, w + 1);
                ok = FALSE;
            }

            if (v == parnt[w] && cst[w] - cst[v] != p->cst)
            {
                fprintf(stderr,
                        "ERRO: validacao.c: arco da arborescencia %d-%d nao e justo\n",
                        v + 1, w + 1);
                fprintf(stderr,
                        "           cst[%d] - cst[%d] != %d == c[%d-%d]\n",
                        w + 1, v + 1, p->cst, v + 1, w + 1);
                ok = FALSE;
            }

        }
    }

    return ok;
}


/*
    digraphDfsR(T,lbl,cnt)
    Recebe uma flotesta T, rotulos lbl dos vertics e

    Usado para verifica se uma floresta e geradora minima.
 */
Bool
digraphDfsR(Graph T, int lbl[], int cnt)
{
    int a;
    Vertex v;
    int indicadorArvoreGer;

    cnt = 0;
    indicadorArvoreGer = TRUE;

    for(v = 0; v < T->V; v++)
    {
        lbl[v] = -1;
    }

    a = dfsR(T, 1, lbl, cnt);

    if (a != T->V)
    {
        indicadorArvoreGer = FALSE;
    }

    return indicadorArvoreGer;
}

int
dfsR(Graph T, Vertex v, int lbl[], int cnt)
{
    link p;
    int nVertices;

    nVertices = 0;
    lbl[v] = 0;         /* o  vertice v foi atingido */

    for(p = T->adj[v]; p; p = p->next)
    {
        if(lbl[p->w] == -1)
        {
            nVertices += dfsR(T, p->w , lbl, cnt);
        }
    }

    return nVertices + 1;
}


int
verificaMst(Graph T, Digraph G)
{
    int arvoreOk = TRUE ;
    int custoArestaArvore;
    link p, q, aux;
    Vertex v, w, r, s;

    printf("\n");
    AVISO(validacao.c: Verificando arvore geradora minima...);
    if((T->A)/2 != T->V - 1)
    {
        AVISO(validacao.c : Erro encontrado: Numero de arestas incompativel!);
        arvoreOk = FALSE;
    }

    /* armazena o corte em arvore geradora */
    if (!(lbl = mallocSafe((G->V) * sizeof(int))))
    {
        fprintf(stderr,"PRINT: validacao.c: nao consegui alocar vetor 'lbl' (%d)\n",
                G->V);
        digraphFree(G);
        return EXIT_FAILURE;
    }

    if(!digraphDfsR(T, lbl, cnt))
    {
        AVISO(validacao.c: Nao eh arvore geradora);
        arvoreOk = FALSE;
    }

    for(v = 0; v < T->V; v++)
    {
        p = T->adj[v];
        while(p)
        {
            /* rotula os vertices de T -{vw} */
            w = p->w;
            custoArestaArvore = p->cst;
            aux = p->next;
            graphRemoveE(T, v, w);
            digraphDfsR(T, lbl, cnt);
            graphInsertE(T, v, w, custoArestaArvore);
            p = aux;

            /* verifica todas as arestas do grafo que estao no
               corte fundamental determinado por T - {vw} */

	    for (r = 0; r < G->V; r++)
	    {
            for(q = G->adj[r]; q; q = q->next)
            {
                s = q->w;
                if(lbl[r] != lbl[s] && custoArestaArvore > q->cst)
                {
                    ERRO(validacao.c: a arvore nao eh minima!);
                    arvoreOk = FALSE;
                }
            }
	    }
        }
    }

    if (!arvoreOk)
    {
        ERRO(validacao.c: arvore nao e minima.);
    }
    else
    {
        AVISO(validacao.c: a arvore eh arvore geradora minima!);
    }

    free(lbl);
    return arvoreOk;
}
