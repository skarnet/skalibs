/* ISC license. */

#include <sys/types.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>

int skaclient_put (skaclient_t *a, char const *s, size_t len, unixmessage_handler_func_t *cb, void *result)
{
  unixmessage_t m = { .s = (char *)s, .len = len, .fds = 0, .nfds = 0 } ;
  return skaclient_putmsg(a, &m, cb, result) ;
}
