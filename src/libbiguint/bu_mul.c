/* ISC license. */

#include <stdint.h>
#include <skalibs/uint64.h>
#include <skalibs/biguint.h>

 /* No Karatsuba. Keep it simple, stupid. */

int bu_mul (uint32_t *x, unsigned int xn, uint32_t const *a, unsigned int an, uint32_t const *b, unsigned int bn)
{
  unsigned int alen = bu_len(a, an) ;
  unsigned int blen = bu_len(b, bn) ;
  uint32_t c[alen + blen] ;
  register unsigned int i = 0 ;
  bu_zero(c, alen + blen) ;
  for (; i < alen ; i++)
  {
    register uint32_t carry = 0 ;
    register unsigned int j = 0 ;
    for (; j < blen ; j++)
    {
      register uint64 t = a[i] ;
      t *= b[j] ;
      t += c[i+j] ;
      t += carry ;
      c[i+j] = (uint32_t)t ;
      carry = (uint32_t)(t >> 32) ;
    }
    c[i+j] += carry ;
  }
  return bu_copy(x, xn, c, alen+blen) ;
}
