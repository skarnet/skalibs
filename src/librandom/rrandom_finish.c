/* ISC license. */

#include <skalibs/unirandom.h>
#include <skalibs/rrandom.h>

int rrandom_finish (rrandom_ref z)
{
  rrandom zero = RRANDOM_ZERO ;
  unsigned int i = z->n ;
  int e = 1 ;
  while (i--) e &= unirandom_finish(&z->tries[i].it) ;
  if (e) *z = zero ;
  return e ;
}
