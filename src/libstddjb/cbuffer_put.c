/* ISC license. */

#include <skalibs/cbuffer.h>
#include <skalibs/siovec.h>

unsigned int cbuffer_put (cbuffer_t *b, char const *s, unsigned int len)
{
  siovec_t v[2] ;
  cbuffer_wpeek(b, v) ;
  return cbuffer_WSEEK(b, siovec_scatter(v, 2, s, len)) ;
}
