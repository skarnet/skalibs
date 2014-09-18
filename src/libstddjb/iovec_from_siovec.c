/* ISC license. */

#include <sys/types.h>
#include <sys/uio.h>
#include <skalibs/siovec.h>

void iovec_from_siovec (struct iovec *iov, siovec_t const *v, unsigned int n)
{
  while (n--)
  {
    iov[n].iov_base = v[n].s ;
    iov[n].iov_len = v[n].len ;
  }
}
