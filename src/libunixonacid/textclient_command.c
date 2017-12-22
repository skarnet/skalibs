/* ISC license. */

#include <sys/uio.h>
#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/textclient.h>

int textclient_command (textclient_t *a, char const *s, size_t len, tain_t const *deadline, tain_t *stamp)
{
  struct iovec ans ;
  if (!textclient_exchange(a, s, len, &ans, deadline, stamp)) return 0 ;
  if (ans.iov_len != 1) return (errno = EPROTO, 0) ;
  if (*(char *)ans.iov_base) return (errno = *(char *)ans.iov_base, 0) ;
  return 1 ;
}
