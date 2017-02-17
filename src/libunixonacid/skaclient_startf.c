/* ISC license. */

#include <sys/types.h>
#include <stdint.h>
#include <errno.h>
#include <skalibs/kolbak.h>
#include <skalibs/skaclient.h>
#include <skalibs/tai.h>
#include "skaclient-internal.h"

int skaclient_startf (
  skaclient_t *a,
  char *bufss,
  size_t bufsn,
  char *auxbufss,
  size_t auxbufsn,
  char *bufas,
  size_t bufan,
  char *auxbufas,
  size_t auxbufan,
  kolbak_closure_t *q,
  size_t qlen,
  char const *prog,
  char const *const *argv,
  char const *const *envp,
  uint32_t options,
  char const *before,
  size_t beforelen,
  char const *after,
  size_t afterlen,
  tain_t const *deadline,
  tain_t *stamp)
{
  skaclient_cbdata_t blah ;
  unixmessage_t m ;
  int r ;
  if (!skaclient_startf_async(a, bufss, bufsn, auxbufss, auxbufsn, bufas, bufan, auxbufas, auxbufan, q, qlen, prog, argv, envp, options, before, beforelen, after, afterlen, &blah)) return 0 ;
  if (!skaclient_timed_flush(a, deadline, stamp))
  {
    int e = errno ;
    skaclient_end(a) ;
    errno = e ;
    return 0 ;
  }
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
