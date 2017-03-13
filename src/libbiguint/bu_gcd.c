/* ISC license. */

#include <skalibs/biguint.h>

int bu_gcd (uint32_t *r, unsigned int rn, uint32_t const *a, unsigned int an, uint32_t const *b, unsigned int bn)
{
  if (bu_cmp(a, an, b, bn) < 0)
  {
    uint32_t const *t = a ;
    unsigned int tn = an ;
    a = b ; an = bn ;
    b = t ; bn = tn ;
  }
  {
    uint32_t trash[an] ;
    uint32_t aa[an] ;
    uint32_t bb[an] ;
    uint32_t *aaa = aa, *bbb = bb ;
    bu_copy_internal(aa, a, an) ;
    bu_copy_internal(bb, b, bn) ;
    bu_zero(bb+bn, an-bn) ;

    while (bu_len(bbb, an))
    {
      uint32_t *ttt = aaa ;
      bu_div_internal(aaa, an, bbb, an, trash, an) ;
      aaa = bbb ;
      bbb = ttt ;
    }
    return bu_copy(r, rn, aaa, an) ;
  }
}
