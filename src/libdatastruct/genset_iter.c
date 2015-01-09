/* ISC license. */

#include <skalibs/bitarray.h>
#include <skalibs/functypes.h>
#include <skalibs/genset.h>

unsigned int genset_iter_nocancel (genset *g, unsigned int n, iterfunc_t_ref f, void *stuff)
{
  unsigned char bits[bitarray_div8(n)] ;
  unsigned int i = 0, j = 0, m = genset_n(g) ;
  bitarray_setn(bits, 0, n) ;
  for (; i < g->sp ; i++) if (g->freelist[i] < n) bitarray_clear(bits, g->freelist[i]) ;
  for (i = 0 ; (i < n) && (j < m) ; i++) if (bitarray_peek(bits, i))
  {
    j++ ;
    if (!(*f)(g->storage + i * g->esize, stuff)) break ;
  }
  return i ;
}
