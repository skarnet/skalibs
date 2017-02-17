/* ISC license. */

#include <sys/uio.h>
#include <skalibs/skaclient.h>
#include <skalibs/tai.h>
#include <skalibs/unixmessage.h>

int skaclient_sendv (skaclient_t *a, struct iovec const *v, unsigned int vlen, unixmessage_handler_func_t *cb, void *result, tain_t const *deadline, tain_t *stamp)
{
  unixmessage_v_t m = { .v = (struct iovec *)v, .vlen = vlen, .fds = 0, .nfds = 0 } ;
  return skaclient_sendmsgv(a, &m, cb, result, deadline, stamp) ;
}
