/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

/*
   u = u/a mod m. a and m must be relatively prime - otherwise, infinite loop.
   a is not immutable.
   Original idea: see http://research.sun.com/techrep/2001/abstract-95.html
*/

void bu_divmod_internal (register uint32 *u, register uint32 *a, register uint32 const *m, unsigned int n)
{
  uint32 bb[n] ; register uint32 *b = bb ;
  uint32 vv[n] ; register uint32 *v = vv ;
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
      register uint32 *t = a ; a = b ; b = t ;
      t = u ; u = v ; v = t ;
    }
    bu_add(a, n, a, n, b, n) ;
    bu_add(u, n, u, n, v, n) ;
  }
}
