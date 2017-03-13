/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/iopause.h>
#include <skalibs/unix-timed.h>

ssize_t timed_get (void *b, initfunc_t_ref getfd, getfunc_t_ref get, tain_t const *deadline, tain_t *stamp)
{
  iopause_fd x = { .fd = (*getfd)(b), .events = IOPAUSE_READ, .revents = 0 } ;
  ssize_t r = (*get)(b) ;
  while (!r)
  {
    r = iopause_stamp(&x, 1, deadline, stamp) ;
    if (!r) return (errno = ETIMEDOUT, -1) ;
    else if (r > 0 && x.revents & (IOPAUSE_READ | IOPAUSE_EXCEPT)) r = (*get)(b) ;
  }
  return unsanitize_read(r) ;
}
