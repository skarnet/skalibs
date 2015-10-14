/* ISC license. */

#include <skalibs/uint64.h>
#include "djbtime-internal.h"

void leapsecs_add (uint64 *t, int hit)
{
  uint64 u = *t ;
  register unsigned int i = 0 ;
  for (; i < leapsecs_table_len ; i++)
  {
    if (u < leapsecs_table[i]) break ;
    if (!hit || (leapsecs_table[i] < u)) ++u ;
  }
  *t = u ;
}
