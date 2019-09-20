/* ISC license. */

#include <stdlib.h>
#include <skalibs/alloc.h>

int alloc_realloc (void **x, size_t n)
{
  void *y = n ? realloc(*x, n) : (free(*x), alloc(0)) ;
  if (!y) return 0 ;
  *x = y ;
  return 1 ;
}
