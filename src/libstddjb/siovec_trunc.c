/* ISC license. */

#include <sys/uio.h>
#include <skalibs/siovec.h>

unsigned int siovec_trunc (struct iovec *v, unsigned int n, size_t len)
{
  size_t w = siovec_len(v, n) ;
  unsigned int i = n ;
  if (w < len) return n ;
  len = w - len ;
  while (len && i--)
  {
    w = len > v[i].iov_len ? v[i].iov_len : len ;
    v[i].iov_len -= w ; len -= w ;
  }
  return i ;
}
