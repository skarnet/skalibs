/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/error.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>
#include "skaclient-internal.h"

int skaclient_start_cb (unixmessage_t const *m, skaclient_cbdata_t *blah)
{
  if (m->len != blah->afterlen
   || byte_diff(m->s, m->len, blah->after)
   || m->nfds != 1) return (errno = EPROTO, 0) ;
  blah->asyncin->fd = m->fds[0] ;
  blah->asyncout->fd = m->fds[0] ;
  return 1 ;
}
