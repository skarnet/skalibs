/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>

int buffer_getall (buffer *b, char *buf, unsigned int len, unsigned int *w)
{
  if (*w > len) return (errno = EINVAL, -1) ;
  *w += buffer_getnofill(b, buf + *w, len - *w) ;
  while (*w < len)
  {
    register int r = sanitize_read(buffer_fill(b)) ;
    if (r <= 0) return r ;
    *w += buffer_getnofill(b, buf + *w, len - *w) ;
  }
  return 1 ;
}
