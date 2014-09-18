/* ISC license. */

#include <skalibs/uint64.h>
#include "djbtime-internal.h"

int leapsecs_sub_r (uint64 *t, char const *file, uint64 *leapsecs)
{
  uint64 u = *t ;
  uint64 d = 0 ;
  int n = leapsecs_init_r(file, leapsecs) ;
  register unsigned int i = 0 ;
  register int hit = 0 ;
  if (n < 0) return -1 ;
  for (; i < (unsigned int)n ; i++)
  {
    if (u < leapsecs[i]) break ;
    ++d ;
    if (u == leapsecs[i]) hit = 1 ;
  }
  *t = u - d ;
  return hit ;
}
