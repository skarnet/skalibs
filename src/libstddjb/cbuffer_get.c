/* ISC license. */

#include <skalibs/cbuffer.h>
#include <skalibs/siovec.h>

unsigned int cbuffer_get (cbuffer_t *b, char *s, unsigned int len)
{
  siovec_t v[2] ;
  cbuffer_rpeek(b, v) ;
  return cbuffer_RSEEK(b, siovec_gather(v, 2, s, len)) ;
}
