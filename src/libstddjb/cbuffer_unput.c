/* ISC license. */

#include <skalibs/cbuffer.h>

unsigned int cbuffer_unput (cbuffer_t *b, unsigned int len)
{
  register unsigned int max = cbuffer_len(b) ;
  if (len > max) len = max ;
  return cbuffer_UNPUT(b, len) ;
}
