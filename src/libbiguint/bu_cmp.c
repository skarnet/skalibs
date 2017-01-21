/* ISC license. */

#include <stdint.h>
#include <skalibs/biguint.h>

int bu_cmp (register uint32_t const *a, register unsigned int an, register uint32_t const *b, register unsigned int bn)
{
  an = bu_len(a, an) ;
  bn = bu_len(b, bn) ;
  if (an < bn) return -1 ;
  if (an > bn) return 1 ;
  while (bn--)
  {
    if (a[bn] < b[bn]) return -1 ;
    if (a[bn] > b[bn]) return 1 ;
  }
  return 0 ;
}
