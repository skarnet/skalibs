/* ISC license. */

#include <skalibs/biguint.h>

 /* Nope, no Montgomery either. */

int bu_mulmod (uint32_t *c, unsigned int cn, uint32_t const *a, unsigned int an, uint32_t const *b, unsigned int bn, uint32_t const *m, unsigned int mn)
{
  unsigned int alen = bu_len(a, an) ;
  unsigned int blen = bu_len(b, bn) ;
  uint32_t x[alen+blen] ;
  if (!bu_mul(x, alen+blen, a, alen, b, blen)) return 0 ;
  if (!bu_mod(x, alen+blen, m, mn)) return 0 ;
  return bu_copy(c, cn, x, mn) ;
}
