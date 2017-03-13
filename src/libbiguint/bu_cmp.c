/* ISC license. */

#include <skalibs/biguint.h>

int bu_cmp (uint32_t const *a, unsigned int an, uint32_t const *b, unsigned int bn)
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
