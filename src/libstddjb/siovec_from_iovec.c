/* ISC license. */

#include <sys/types.h>
#include <sys/uio.h>
#include <skalibs/siovec.h>

void siovec_from_iovec (siovec_t *v, struct iovec const *iov, unsigned int n)
{
  while (n--)
  {
    v[n].s = iov[n].iov_base ;
    v[n].len = iov[n].iov_len ;
  }
}
