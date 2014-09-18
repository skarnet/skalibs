/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/netstring.h>
#include <skalibs/uint.h>

int netstring_put (buffer *b, char const *s, unsigned int len, unsigned int *written)
{
  char fmt[UINT_FMT] ;
  unsigned int n = uint_fmt(fmt, len) ;
  if (*written > len + n + 2) return (errno = EINVAL, 0) ;
  fmt[n] = ':' ;
  if (*written < n + 1)
  {
    unsigned int w = *written ;
    int r = buffer_putall(b, fmt, n+1, &w) ;
    if (r < 0) return (*written = w, 0) ;
    *written = n+1 ;
  }
  if (*written < n+1 + len)
  {
    unsigned int w = *written - (n+1) ;
    int r = buffer_putall(b, s, len, &w) ;
    *written = w + (n+1) ;
    if (r < 0) return (*written = n+1 + w, 0) ;
    *written = n+1 + len ;
  }
  {
    unsigned int w = 0 ;
    int r = buffer_putall(b, ",", 1, &w) ;
    if (r < 0) return 0 ;
  }
  *written = 0 ;
  return 1 ;
}
