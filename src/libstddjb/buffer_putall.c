/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>

int buffer_putall (buffer *b, char const *s, unsigned int len, unsigned int *written)
{
  if (*written > len) return (errno = EINVAL, 0) ;
  for (;;)
  {
    *written += buffer_putnoflush(b, s + *written, len - *written) ;
    if (*written >= len) return 1 ;
    buffer_flush(b) ;
    if (buffer_isfull(b)) return 0 ;
  }
}
