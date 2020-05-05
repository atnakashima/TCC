#include "union.h"
#include "util.h"

#undef DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif

static Vertex *cor;

static int    *sz;

static Vertex find(Vertex v);

void
ufInit(int n)
{
    Vertex v;

#ifdef DEBUG
    printf("\nDEBUG: union.c: ufInit(%d): entrou\n", n);
#endif

    cor = mallocSafe((n) * sizeof *cor);
    sz  = mallocSafe((n) * sizeof *sz);

    /* começa do 0 pois os vertices do arquivo de entrada foram transladados */
    for(v = 0; v < n; v++)
    {
        cor[v] = v;
        sz[v]  = 1;
    }

#ifdef DEBUG
    printf("DEBUG: union.c: ufInit(%d): saiu\n", n);
#endif

}

int
ufFind(Vertex v, Vertex w)
{

#ifdef DEBUG
    printf("\nDEBUG: union.c: ufFind(%d,%d): entrou\n", v, w);
    printf("find(w) = %d\n", find(w));
#endif

    return find(v) == find(w);
}


void
ufUnion(Vertex v0, Vertex w0)
{
    Vertex v, w;

#ifdef DEBUG
    printf("\nDEBUG: union.c: ufUnion (%d,%d): entrou\n", v0, w0);
#endif

    v = find(v0);
    w = find(w0);

    if (v == w) return;

    if(sz[v] < sz[w])
    {
        cor[v] = cor[w];
        sz[w] += sz[v];
    }
    else
    {
        cor[w] = cor[v];
        sz[v] += sz[w];
    }


#ifdef DEBUG
    printf("DEBUG: union.c: ufUnion: saiu\n");
#endif

}

static
Vertex find(Vertex v)
{

#ifdef DEBUG
    printf("DEBUG: union.c: find(%d): entrou \n", v);
#endif

    while (v != cor[v])
    {
        v = cor[v];
    }

#ifdef DEBUG
    printf("DEBUG: union.c: find: retornou %d \n", v);
#endif

    return v;
}

void
ufFree()
{
    free(cor);
    free(sz);
}
