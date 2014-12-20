/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/gensetdyn.h>

void gensetdyn_init (gensetdyn *g, unsigned int esize, unsigned int base, unsigned int fracnum, unsigned int fracden)
{
  g->storage = stralloc_zero ;
  g->freelist = genalloc_zero ;
  g->esize = esize ;
  g->base = base ;
  g->fracnum = fracnum ;
  g->fracden = fracden ;
}
