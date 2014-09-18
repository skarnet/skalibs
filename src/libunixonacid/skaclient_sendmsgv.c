/* ISC license. */

#include <errno.h>
#include <skalibs/skaclient.h>
#include <skalibs/tai.h>
#include <skalibs/unixmessage.h>

int skaclient_sendmsgv_and_close (skaclient_t *a, unixmessage_v_t const *m, unsigned char const *bits, unixmessage_handler_func_t *cb, void *result, tain_t const *deadline, tain_t *stamp)
{
  register int r ;
  if (!skaclient_putmsgv_and_close(a, m, bits, cb, result)) return 0 ;
  if (!skaclient_timed_flush(a, deadline, stamp)) return 0 ;
  r = skaclient_timed_supdate(a, deadline, stamp) ;
  return r < 0 ? 0 : !r ? (errno = EPIPE, 0) : 1 ;
}
