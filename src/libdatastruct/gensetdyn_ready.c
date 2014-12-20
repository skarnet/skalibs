/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/gensetdyn.h>

int gensetdyn_ready (gensetdyn *g, unsigned int n)
{
  int wasnull = !g->storage.s ;
  unsigned int i = g->storage.len ;
  if (n < i) return 1 ;
  n += g->base + (n * g->fracnum) / g->fracden ;
  if (!stralloc_ready_tuned(&g->storage, n * g->esize, 0, 0, 1)) return 0 ;
  if (!genalloc_ready(unsigned int, &g->freelist, n))
  {
    if (wasnull) stralloc_free(&g->storage) ;
    return 0 ;
  }
  for (; i < n ; i++)
  {
    unsigned int j = n - 1 - i + g->storage.len ;
    genalloc_catb(unsigned int, &g->freelist, &j, 1) ;
  }
  g->storage.len = n ;
  return 1 ;
}
