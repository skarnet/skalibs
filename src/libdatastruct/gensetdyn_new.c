/* ISC license. */

#include <skalibs/genalloc.h>
#include <skalibs/gensetdyn.h>

int gensetdyn_new (gensetdyn_ref g, unsigned int *i)
{
  register unsigned int n ;
  if (!genalloc_len(unsigned int, &g->freelist) && !gensetdyn_readyplus(g, 1)) return 0 ;
  n = genalloc_len(unsigned int, &g->freelist) ;
  *i = genalloc_s(unsigned int, &g->freelist)[n-1] ;
  genalloc_setlen(unsigned int, &g->freelist, n-1) ;
  return 1 ;
}
