
#ifndef _UNION_H
#define _UNION_H

#include "item.h"
#include "digraph.h"

/*#define maxV 10000000*/

void ufInit(int N);

int ufFind(Vertex v, Vertex w);

void ufUnion(Vertex v0, Vertex w0);

void ufFree();


#endif /* UNION_H */
