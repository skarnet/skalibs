/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

int bu_gcd (uint32 *r, unsigned int rn, uint32 const *a, unsigned int an, uint32 const *b, unsigned int bn)
{
  if (bu_cmp(a, an, b, bn) < 0)
  {
    register uint32 const *t = a ;
    register unsigned int tn = an ;
    a = b ; an = bn ;
    b = t ; bn = tn ;
  }
  {
    uint32 trash[an] ;
    uint32 aa[an] ;
    uint32 bb[an] ;
    uint32 *aaa = aa, *bbb = bb ;
    bu_copy_internal(aa, a, an) ;
    bu_copy_internal(bb, b, bn) ;
    bu_zero(bb+bn, an-bn) ;

    while (bu_len(bbb, an))
    {
      register uint32 *ttt = aaa ;
      bu_div_internal(aaa, an, bbb, an, trash, an) ;
      aaa = bbb ;
      bbb = ttt ;
    }
    return bu_copy(r, rn, aaa, an) ;
  }
}
