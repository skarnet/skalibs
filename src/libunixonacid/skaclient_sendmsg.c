/* ISC license. */

#include <skalibs/tai.h>
#include <skalibs/unixmessage.h>
#include <skalibs/skaclient.h>

int skaclient_sendmsg_and_close (skaclient_t *a, unixmessage_t const *m, unsigned char const *bits, unixmessage_handler_func_t_ref cb, void *result, tain_t const *deadline, tain_t *stamp)
{
  return skaclient_putmsg_and_close(a, m, bits, cb, result)
   && skaclient_syncify(a, deadline, stamp) ;
}
