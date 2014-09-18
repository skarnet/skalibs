/* ISC license. */

#include <skalibs/skaclient.h>
#include <skalibs/tai.h>
#include <skalibs/unixmessage.h>

int skaclient_send (skaclient_t *a, char const *s, unsigned int len, unixmessage_handler_func_t *cb, void *result, tain_t const *deadline, tain_t *stamp)
{
  unixmessage_t m = { .s = (char *)s, .len = len, .fds = 0, .nfds = 0 } ;
  return skaclient_sendmsg(a, &m, cb, result, deadline, stamp) ;
}
