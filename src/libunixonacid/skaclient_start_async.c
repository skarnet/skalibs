/* ISC license. */

#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/kolbak.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>
#include <skalibs/webipc.h>
#include "skaclient-internal.h"

int skaclient_start_async (
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
  skaclient_cbdata_t *blah)
{
  int fd = ipc_stream_nbcoe() ;
  if (fd < 0) return 0 ;
  if ((!ipc_connect(fd, path) && !error_isalready(errno))
   || !skaclient_init(a, fd, bufss, bufsn, auxbufss, auxbufsn, bufas, bufan, auxbufas, auxbufan, q, qlen, before, beforelen))
  {
    register int e = errno ;
    fd_close(fd) ;
    errno = e ;
    return 0 ;
  }
  a->pid = 0 ;
  a->options = 0 ;
  if (!kolbak_enqueue(&a->kq, (unixmessage_handler_func_t_ref)&skaclient_start_cb, blah))
  {
    skaclient_end(a) ;
    return 0 ;
  }
  blah->asyncin = &a->asyncin ;
  blah->asyncout = &a->asyncout ;
  blah->after = after ;
  blah->afterlen = afterlen ;
  return 1 ;
}
