/* ISC license. */

#include <sys/types.h>
#include <skalibs/tai.h>
#include <skalibs/unixmessage.h>
#include <skalibs/skaclient.h>

int skaclient_send (skaclient_t *a, char const *s, size_t len, unixmessage_handler_func_t *cb, void *result, tain_t const *deadline, tain_t *stamp)
{
  unixmessage_t m = { .s = (char *)s, .len = len, .fds = 0, .nfds = 0 } ;
  return skaclient_sendmsg(a, &m, cb, result, deadline, stamp) ;
}
