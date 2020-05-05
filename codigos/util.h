#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>  /* fprintf() */
#include <stdlib.h> /* malloc(), exit() */
#include <stddef.h> /* for size_t */

/*-------------------------------------------------------------*/ 
typedef char * String;

/*---------------------------------------------------------------*/
enum bool 
{
    FALSE = 0,
    TRUE  = 1
};
typedef enum bool Bool;

/*-------------------------------------------------------------*/ 
#define ERRO(msg)  fprintf(stderr,"ERRO: %s\n", #msg)

#define AVISO(msg) if (verbose) fprintf(stdout,"AVISO: %s\n", #msg)


/*-------------------------------------------------------------*/ 
void *mallocSafe (size_t nbytes);

#endif
