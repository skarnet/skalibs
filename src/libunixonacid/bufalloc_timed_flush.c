/* ISC license. */

#include <skalibs/bufalloc.h>
#include <skalibs/functypes.h>
#include <skalibs/tai.h>
#include <skalibs/unix-timed.h>

static int bufalloc_isnonempty (bufalloc *ba)
{
  return !!bufalloc_len(ba) ;
}

int bufalloc_timed_flush (bufalloc *ba, tain_t const *deadline, tain_t *stamp)
{
  return timed_flush(ba, (initfunc_t_ref)&bufalloc_getfd, (initfunc_t_ref)&bufalloc_isnonempty, (initfunc_t_ref)&bufalloc_flush, deadline, stamp) ;
}
