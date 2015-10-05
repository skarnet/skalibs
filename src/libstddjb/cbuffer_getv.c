/* ISC license. */

#include <skalibs/cbuffer.h>
#include <skalibs/siovec.h>

unsigned int cbuffer_getv (cbuffer_t *b, siovec_t const *v, unsigned int n)
{
  siovec_t vsrc[2] ;
  register unsigned int w ;
  cbuffer_rpeek(b, vsrc) ;
  w = siovec_deal(v, n, vsrc, 2) ;
  return cbuffer_RSEEK(b, w) ;
}
