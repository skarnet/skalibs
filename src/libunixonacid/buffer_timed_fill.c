/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>
#include <skalibs/functypes.h>
#include <skalibs/tai.h>
#include <skalibs/unix-timed.h>

static int get (buffer *b)
{
  return sanitize_read(buffer_fill(b)) ;
}

int buffer_timed_fill (buffer *b, tain_t const *deadline, tain_t *stamp)
{
  return timed_get(b, (initfunc_t_ref)&buffer_getfd, (initfunc_t_ref)&get, deadline, stamp) ;
}
