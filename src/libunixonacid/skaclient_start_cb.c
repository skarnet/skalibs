/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/error.h>
#include <skalibs/unixmessage.h>
#include <skalibs/skaclient.h>
#include "skaclient-internal.h"

int skaclient_start_cb (unixmessage_t const *m, skaclient_cbdata_t *blah)
{
  if (m->len != blah->afterlen
   || byte_diff(m->s, m->len, blah->after)
   || m->nfds != 1)
  {
    unixmessage_drop(m) ;
    return (errno = EPROTO, 0) ;
  }
  blah->a->asyncin.fd = m->fds[0] ;
  blah->a->asyncout.fd = m->fds[0] ;
  if (!(blah->a->options & SKACLIENT_OPTION_ASYNC_ACCEPT_FDS))
    unixmessage_receiver_refuse_fds(&blah->a->asyncin) ;
  if (!(blah->a->options & SKACLIENT_OPTION_SYNC_ACCEPT_FDS))
    unixmessage_receiver_refuse_fds(&blah->a->syncin) ;
  return 1 ;
}
