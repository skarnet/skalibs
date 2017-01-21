/* ISC license. */

#include <stdint.h>
#include <errno.h>
#include <skalibs/biguint.h>

/*
   q = y/x mod m.
*/

int bu_divmod (uint32_t *q, unsigned int qn, uint32_t const *y, unsigned int yn, uint32_t const *x, unsigned int xn, uint32_t const *m, unsigned int mn)
{
  unsigned int ylen = bu_len(y, yn) ;
  unsigned int xlen = bu_len(x, xn) ;
  unsigned int mlen = bu_len(m, mn) ;
  unsigned int n = ylen ;
  if (n < xlen) n = xlen ;
  if (n < mlen) n = mlen ;
  if (!n) return (errno = EDOM, 0) ;
  {
    uint32_t yy[n] ;
    uint32_t xx[n] ;
    uint32_t mm[n] ;
    bu_gcd(xx, n, x, xlen, m, mlen) ;
    if ((xx[0] != 1) || (bu_len(xx, n) != 1)) return (errno = EDOM, 0) ;
    bu_copy_internal(yy, y, ylen) ; bu_zero(yy+ylen, n-ylen) ;
    bu_copy_internal(xx, x, xlen) ; bu_zero(xx+xlen, n-xlen) ;
    bu_copy_internal(mm, m, mlen) ; bu_zero(mm+mlen, n-mlen) ;
    bu_divmod_internal(yy, xx, mm, n) ;
    return bu_copy(q, qn, yy, n) ;
  }
}
