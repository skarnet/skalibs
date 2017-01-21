/* ISC license. */

#include <stdint.h>
#include <skalibs/biguint.h>

/*
   u = u/a mod m. a and m must be relatively prime - otherwise, infinite loop.
   a is not immutable.
   Original idea: see http://research.sun.com/techrep/2001/abstract-95.html
*/

void bu_divmod_internal (register uint32_t *u, register uint32_t *a, register uint32_t const *m, unsigned int n)
{
  uint32_t bb[n] ; register uint32_t *b = bb ;
  uint32_t vv[n] ; register uint32_t *v = vv ;
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
      register uint32_t *t = a ; a = b ; b = t ;
      t = u ; u = v ; v = t ;
    }
    bu_add(a, n, a, n, b, n) ;
    bu_add(u, n, u, n, v, n) ;
  }
}
