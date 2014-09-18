/* ISC license. */

#include <errno.h>
#include <skalibs/kolbak.h>
#include <skalibs/skaclient.h>
#include <skalibs/tai.h>
#include "skaclient-internal.h"

int skaclient_start (
  skaclient_t *a,
  char *bufss,
  unsigned int bufsn,
  char *auxbufss,
  unsigned int auxbufsn,
  char *bufas,
  unsigned int bufan,
  char *auxbufas,
  unsigned int auxbufan,
  kolbak_closure_t *q,
  unsigned int qlen,
  char const *path,
  char const *before,
  unsigned int beforelen,
  char const *after,
  unsigned int afterlen,
  tain_t const *deadline,
  tain_t *stamp)
{
  skaclient_cbdata_t blah ;
  unixmessage_t m ;
  register int r ;
  if (!skaclient_start_async(a, bufss, bufsn, auxbufss, auxbufsn, bufas, bufan, auxbufas, auxbufan, q, qlen, path, before, beforelen, after, afterlen, &blah)) return 0 ;
  r = unixmessage_timed_receive(&a->syncin, &m, deadline, stamp) ;
  if (r < 1)
  {
    int e = errno ;
    if (!r) e = EPIPE ;
    skaclient_end(a) ;
    errno = e ;
    return 0 ;
  }
  return kolbak_call(&m, &a->kq) ;
}
