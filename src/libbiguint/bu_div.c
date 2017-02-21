/* ISC license. */

#include <stdint.h>
#include <errno.h>
#include <skalibs/biguint.h>

int bu_div (uint32_t const *a, unsigned int an, uint32_t const *b, unsigned int bn, uint32_t *q, unsigned int qn, uint32_t *r, unsigned int rn)
{
  unsigned int alen = bu_len(a, an) ;
  unsigned int blen = bu_len(b, bn) ;
  if (!blen) return (errno = EDOM, 0) ;
  else
  {
    uint32_t qq[alen] ;
    uint32_t rr[alen] ;
    int qh, rh ;
    bu_copy_internal(rr, a, alen) ;
    bu_div_internal(rr, alen, b, blen, qq, alen) ;
    qh = bu_copy(q, qn, qq, alen) ;
    rh = bu_copy(r, rn, rr, alen) ;
    return qh && rh ;
  }
}
