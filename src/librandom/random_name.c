/* ISC license. */

/* MT-unsafe */

#include "random-internal.h"
#include <skalibs/random.h>

int random_name (char *s, unsigned int n)
{
  register unsigned int r = rrandom_name(&badrandom_here, s, n, 1) ;
  if (r < n) return -1 ;
  return n ;
}
