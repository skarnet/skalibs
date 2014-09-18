/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/buffer.h>
#include <skalibs/skamisc.h>

int getlnmax (buffer *b, char *d, unsigned int max, unsigned int *w, char sep)
{
  if (max < *w) return (errno = EINVAL, -1) ;
  for (;;)
  {
    siovec_t v[2] ;
    unsigned int len = buffer_len(b) ;
    unsigned int pos ;
    int r ;
    buffer_rpeek(b, v) ;
    if (len > max - *w) len = max - *w ;
    pos = siovec_bytechr(v, 2, sep) ;
    if (pos > len) pos = len ;
    r = pos < len ;
    buffer_getnofill(b, d + *w, pos + r) ; *w += pos ;
    if (*w >= max) return (errno = ERANGE, -1) ;
    if (r) return 1 ;
    r = buffer_fill(b) ;
    if (r <= 0) return r ;
  }
}
