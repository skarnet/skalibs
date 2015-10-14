/* ISC license. */

#include <skalibs/uint64.h>
#include "djbtime-internal.h"

int leapsecs_sub (uint64 *t)
{
  uint64 u = *t ;
  uint64 d = 0 ;
  register unsigned int i = 0 ;
  register int hit = 0 ;
  for (; i < leapsecs_table_len ; i++)
  {
    if (u < leapsecs_table[i]) break ;
    ++d ;
    if (u == leapsecs_table[i]) hit = 1 ;
  }
  *t = u - d ;
  return hit ;
}
