/* ISC license. */

#include <skalibs/cbuffer.h>

size_t cbuffer_unput (cbuffer_t *b, size_t len)
{
  size_t max = cbuffer_len(b) ;
  if (len > max) len = max ;
  return cbuffer_UNPUT(b, len) ;
}
