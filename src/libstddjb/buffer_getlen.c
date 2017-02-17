/* ISC license. */

#include <sys/types.h>
#include <skalibs/buffer.h>

size_t buffer_getlen (buffer const *b)
{
  return buffer_len(b) ;
}
