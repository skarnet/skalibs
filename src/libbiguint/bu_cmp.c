/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

int bu_cmp (register uint32 const *a, register unsigned int an, register uint32 const *b, register unsigned int bn)
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
