/* ISC license. */

#include <stdint.h>
#include <errno.h>
#include <skalibs/biguint.h>

/*
   q = a/b, a = a mod b. Assumes b != 0 and qn >= alen - blen + 1.
*/

void bu_div_internal (uint32_t *a, unsigned int an, uint32_t const *b, unsigned int bn, uint32_t *q, unsigned int qn)
{
  unsigned int alen = bu_len(a, an) ;
  unsigned int blen = bu_len(b, bn) ;
  bu_zero(q, qn) ;
  if (alen < blen) return ;
  {
    uint32_t bb[alen + 1] ;
    unsigned int i = 1 + ((alen - blen) << 5) ;
    bu_zero(bb, alen - blen) ;
    bu_copy_internal(bb + alen - blen, b, blen) ;
    bb[alen] = 0 ;

    while (bu_cmp(a, alen, bb, alen+1) >= 0)
    {
      bu_slb(bb + alen - blen, blen + 1) ;
      i++ ;
    }
    while (i && (bu_cmp(a, alen, bb, alen+1) < 0))
    {
      bu_srb(bb, alen + 1) ;
      i-- ;
    }

    while (i--)
    {
      bu_slb(q, alen - blen + 1) ;
      if (bu_cmp(a, alen, bb, alen) >= 0)
      {
        bu_sub(a, alen, a, alen, bb, alen) ;
        q[0] |= 1 ;
      }
      bu_srb(bb, alen) ;
    }
  }
}
