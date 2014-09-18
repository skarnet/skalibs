/* ISC license. */

#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>

int skaclient_default_cb (unixmessage_t const *m, void *p)
{
  unsigned char *err = p ;
  if (m->len != 1 || m->nfds) return (errno = EPROTO, 0) ;
  *err = m->s[0] ;
  return 1 ;
}
