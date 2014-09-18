/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

/* x^-1 mod m. */

int bu_invmod (uint32 *x, unsigned int xn, uint32 const *m, unsigned int mn)
{
  uint32 const one = 1 ;
  return bu_divmod(x, xn, &one, 1, x, xn, m, mn) ;
}
