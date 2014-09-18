/* ISC license. */

#include <skalibs/uint64.h>
#include "djbtime-internal.h"

int leapsecs_add_r (uint64 *t, char const *file, uint64 *leapsecs, int hit)
{
  uint64 u = *t ;
  int n = leapsecs_init_r(file, leapsecs) ;
  register unsigned int i = 0 ;
  if (n < 0) return -1 ;
  for (; i < (unsigned int)n ; i++)
  {
    if (u < leapsecs[i]) break ;
    if (!hit || (leapsecs[i] < u)) ++u ;
  }
  *t = u ;
  return n ;
}
