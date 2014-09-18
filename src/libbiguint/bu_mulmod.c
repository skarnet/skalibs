/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

 /* Nope, no Montgomery either. */

int bu_mulmod (uint32 *c, unsigned int cn, uint32 const *a, unsigned int an, uint32 const *b, unsigned int bn, uint32 const *m, unsigned int mn)
{
  unsigned int alen = bu_len(a, an) ;
  unsigned int blen = bu_len(b, bn) ;
  uint32 x[alen+blen] ;
  if (!bu_mul(x, alen+blen, a, alen, b, blen)) return 0 ;
  if (!bu_mod(x, alen+blen, m, mn)) return 0 ;
  return bu_copy(c, cn, x, mn) ;
}
