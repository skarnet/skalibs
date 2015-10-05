/* ISC license. */

#include <skalibs/cbuffer.h>
#include <skalibs/siovec.h>

unsigned int cbuffer_get (cbuffer_t *b, char *s, unsigned int len)
{
  siovec_t v[2] ;
  register unsigned int w ;
  cbuffer_rpeek(b, v) ;
  w = siovec_gather(v, 2, s, len) ;
  return cbuffer_RSEEK(b, w) ;
}
