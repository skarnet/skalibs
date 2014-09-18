/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/netstring.h>
#include <skalibs/tai.h>
#include <skalibs/iopause.h>
#include <skalibs/unix-timed.h>

int netstring_timed_get (buffer *b, stralloc *sa, tain_t const *deadline, tain_t *stamp)
{
  iopause_fd x = { .fd = buffer_fd(b), .events = IOPAUSE_READ } ;
  unsigned int w = 0 ;
  for (;;)
  {
    register int r = netstring_get(b, sa, &w) ;
    if (r > 0) return r ;
    if (r < 0) return 0 ;
    r = iopause_stamp(&x, 1, deadline, stamp) ;
    if (r < 0) return 0 ;
    else if (!r) return (errno = ETIMEDOUT, 0) ;
  }
}
