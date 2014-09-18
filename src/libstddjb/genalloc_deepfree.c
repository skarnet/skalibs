/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>

void genalloc_deepfree_size (genalloc *g, freefunc_t_ref f, unsigned int size)
{
  unsigned int len = g->len / size ;
  register unsigned int i = 0 ;
  for (; i < len ; i++) (*f)(g->s + i * size) ;
  stralloc_free(g) ;
}
