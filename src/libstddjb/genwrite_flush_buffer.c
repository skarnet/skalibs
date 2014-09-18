/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/genwrite.h>

int genwrite_flush_buffer (void *target)
{
  register buffer *b = target ;
  return buffer_flush(b) ;
}
