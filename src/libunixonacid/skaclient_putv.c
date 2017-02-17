/* ISC license. */

#include <sys/uio.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>

int skaclient_putv (skaclient_t *a, struct iovec const *v, unsigned int vlen, unixmessage_handler_func_t *cb, void *result)
{
  unixmessage_v_t m = { .v = (struct iovec *)v, .vlen = vlen, .fds = 0, .nfds = 0 } ;
  return skaclient_putmsgv(a, &m, cb, result) ;
}
