/* ISC license. */

#include <errno.h>
#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

int bu_div (uint32 const *a, unsigned int an, uint32 const *b, unsigned int bn, uint32 *q, unsigned int qn, uint32 *r, unsigned int rn)
{
  unsigned int alen = bu_len(a, an) ;
  unsigned int blen = bu_len(b, bn) ;
  if (!blen) return (errno = EDOM, 0) ;
  else
  {
    uint32 qq[alen] ;
    uint32 rr[alen] ;
    register int qh, rh ;
    bu_copy_internal(rr, a, alen) ;
    bu_div_internal(rr, alen, b, blen, qq, alen) ;
    qh = bu_copy(q, qn, qq, alen) ;
    rh = bu_copy(r, rn, rr, alen) ;
    return qh && rh ;
  }
}
