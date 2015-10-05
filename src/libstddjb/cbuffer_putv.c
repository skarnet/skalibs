/* ISC license. */

#include <skalibs/cbuffer.h>
#include <skalibs/siovec.h>

unsigned int cbuffer_putv (cbuffer_t *b, siovec_t const *v, unsigned int n)
{
  siovec_t vdest[2] ;
  register unsigned int w ;
  cbuffer_wpeek(b, vdest) ;
  w = siovec_deal(vdest, 2, v, n) ;
  return cbuffer_WSEEK(b, w) ;
}
