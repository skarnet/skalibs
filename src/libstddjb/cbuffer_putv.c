/* ISC license. */

#include <skalibs/cbuffer.h>
#include <skalibs/siovec.h>

unsigned int cbuffer_putv (cbuffer_t *b, siovec_t const *v, unsigned int n)
{
  siovec_t vdest[2] ;
  cbuffer_wpeek(b, vdest) ;
  return cbuffer_WSEEK(b, siovec_deal(vdest, 2, v, n)) ;
}
