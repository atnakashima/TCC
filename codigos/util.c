#include "util.h"

/*-------------------------------------------------------------*/
/*  mallocSafe

   O parâmetro de mallocSafe é do tipo size_t.
   Em muitos computadores, size_t é equivalente a unsigned int.
   A função mallocSafe não está em nenhuma biblioteca e é desconhecida
   fora destas notas de aula.
   Ela é apenas uma abreviatura conveniente.

   Fonte:  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
 */

void *
mallocSafe (size_t nbytes)
{
   void *ptr;

   ptr = malloc (nbytes);
   if (ptr == NULL)
   {
        ERRO(util.c: Socorro! malloc devolveu NULL!);
        exit (EXIT_FAILURE);
   }

   return ptr;
}

