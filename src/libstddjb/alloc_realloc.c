/* ISC license. */

#include <stdlib.h>
#include <skalibs/alloc.h>

int alloc_realloc (char **x, size_t n)
{
  char *y = n ? (char *)realloc(*x, n) : (free(*x), (char *)alloc(0)) ;
  if (!y) return 0 ;
  *x = y ;
  return 1 ;
}
