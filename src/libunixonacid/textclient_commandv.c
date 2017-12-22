/* ISC license. */

#include <sys/uio.h>
#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/textclient.h>

int textclient_commandv (textclient_t *a, struct iovec const *v, unsigned int n, tain_t const *deadline, tain_t *stamp)
{
  struct iovec ans ;
  if (!textclient_exchangev(a, v, n, &ans, deadline, stamp)) return 0 ;
  if (ans.iov_len != 1) return (errno = EPROTO, 0) ;
  if (*(char *)ans.iov_base) return (errno = *(char *)ans.iov_base, 0) ;
  return 1 ;
}
