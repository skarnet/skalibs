/* ISC license. */

#include <skalibs/bitarray.h>
#include <skalibs/functypes.h>
#include <skalibs/gensetdyn.h>

unsigned int gensetdyn_iter (gensetdyn *g, iterfunc_t_ref f, void *stuff)
{
 /*
    XXX: we may be called by a freeing function, so we cannot alloc -
    XXX: so pray that the bitarray fits in the stack.
 */
  unsigned char bits[bitarray_div8(g->storage.len)] ;
  unsigned int i = 0, j = 0, n = 0, m = gensetdyn_n(g) ;
  register unsigned int *fl = genalloc_s(unsigned int, &g->freelist) ;
  register unsigned int sp = genalloc_len(unsigned int, &g->freelist) ;
  bitarray_setn(bits, 0, g->storage.len) ;
  
  for (; i < sp ; i++) bitarray_clear(bits, fl[i]) ;
  for (i = 0 ; (i < g->storage.len) && (j < m) ; i++) if (bitarray_peek(bits, i))
  {
    j++ ;
    if ((*f)(gensetdyn_p(g, i), stuff)) n++ ;
  }
  return n ;
}
