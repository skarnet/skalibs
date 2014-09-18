/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/siovec.h>

int buffer_flush1read (int fd, siovec_t const *v, unsigned int n, void *aux)
{
  if (!buffer_flush(buffer_1)) return -1 ;
  return buffer_read(fd, v, n, aux) ;
}
