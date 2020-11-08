/* ISC license. */

#include <skalibs/biguint.h>

/*
   u = u/a mod m. a and m must be relatively prime - otherwise, infinite loop.
   a is not immutable.
   Original idea by Sheueling Chang Shantz of Sun Research.
*/

void bu_divmod_internal (uint32_t *u, uint32_t *a, uint32_t const *m, unsigned int n)
{
  uint32_t bb[n] ; uint32_t *b = bb ;
  uint32_t vv[n] ; uint32_t *v = vv ;
  bu_copy_internal(b, m, n) ;
  bu_zero(v, n) ;

 /*** XXX: this iterates like mad, should probably be optimized more */
  for (;;)
  {
    while (!(a[0] & 1))
    {
      bu_srb(a, n) ;
      if (u[0] & 1) bu_add(u, n, u, n, m, n) ;
      bu_srb(u, n) ;
    }
    if ((a[0] == 1) && (bu_len(a, n) == 1)) break ;
    if (bu_cmp(a, n, b, n) < 0)
    {
      uint32_t *t = a ; a = b ; b = t ;
      t = u ; u = v ; v = t ;
    }
    bu_add(a, n, a, n, b, n) ;
    bu_add(u, n, u, n, v, n) ;
  }
}
