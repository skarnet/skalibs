/* ISC license. */

#include <skalibs/bitarray.h>
#include <skalibs/functypes.h>
#include <skalibs/genset.h>

unsigned int genset_iter (genset_ref g, iterfunc_t_ref f, void *stuff)
{
  unsigned char bits[bitarray_div8(g->max)] ;
  unsigned int i = 0, j = 0, n = 0, m = genset_n(g) ;
  bitarray_setn(bits, 0, g->max) ;
  for (; i < g->sp ; i++) bitarray_clear(bits, g->freelist[i]) ;
  for (i = 0 ; (i < g->max) && (j < m) ; i++) if (bitarray_peek(bits, i))
  {
    j++ ;
    if ((*f)(g->storage + i * g->esize, stuff)) n++ ;
  }
  return n ;
}
