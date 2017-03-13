/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>
#include <skalibs/functypes.h>
#include <skalibs/unix-timed.h>

static ssize_t get (buffer *b)
{
  return sanitize_read(buffer_fill(b)) ;
}

ssize_t buffer_timed_fill (buffer *b, tain_t const *deadline, tain_t *stamp)
{
  return timed_get(b, (initfunc_t_ref)&buffer_getfd, (getfunc_t_ref)&get, deadline, stamp) ;
}
