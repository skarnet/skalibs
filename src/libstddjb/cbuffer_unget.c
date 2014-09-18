/* ISC license. */

#include <skalibs/cbuffer.h>

unsigned int cbuffer_unget (cbuffer_t *b, unsigned int len)
{
  register unsigned int max = cbuffer_available(b) ;
  if (len > max) len = max ;
  return cbuffer_UNGET(b, len) ;
}
