/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/gensetdyn.h>

void gensetdyn_free (gensetdyn *g)
{
  stralloc_free(&g->storage) ;
  genalloc_free(unsigned int, &g->freelist) ;
  *g = gensetdyn_zero ;
}
