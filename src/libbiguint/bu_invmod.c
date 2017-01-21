/* ISC license. */

#include <stdint.h>
#include <skalibs/biguint.h>

/* x^-1 mod m. */

int bu_invmod (uint32_t *x, unsigned int xn, uint32_t const *m, unsigned int mn)
{
  uint32_t const one = 1 ;
  return bu_divmod(x, xn, &one, 1, x, xn, m, mn) ;
}
