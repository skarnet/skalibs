/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/functypes.h>
#include <skalibs/unix-timed.h>

static int buffer_isnonempty (buffer *b)
{
  return !buffer_isempty(b) ;
}

int buffer_timed_flush (buffer *b, tain_t const *deadline, tain_t *stamp)
{
  return timed_flush(b, (initfunc_t_ref)&buffer_getfd, (initfunc_t_ref)&buffer_isnonempty, (initfunc_t_ref)&buffer_flush, deadline, stamp) ;
}
