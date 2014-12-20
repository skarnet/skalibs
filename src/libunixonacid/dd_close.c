/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

int dd_close (dirdescriptor_t *dd)
{
  return (fd_close(dd->fd) >= 0) ;
}
