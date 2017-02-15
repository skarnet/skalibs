/* ISC license. */

#include <sys/types.h>
#include <string.h>
#include <sys/uio.h>
#include <skalibs/stralloc.h>

int stralloc_catv (stralloc *sa, struct iovec const *v, unsigned int n)
{
  register unsigned int i = 0 ;
  {
    size_t total = 0 ;
    for (; i < n ; i++) total += v[i].iov_len ;
    if (!stralloc_readyplus(sa, total)) return 0 ;
  }
  for (i = 0 ; i < n ; i++)
  {
    memmove(sa->s + sa->len, v[i].iov_base, v[i].iov_len) ;
    sa->len += v[i].iov_len ;
  }
  return 1 ;
}
