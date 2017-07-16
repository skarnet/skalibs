/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

void dd_close (dirdescriptor_t *dd)
{
  fd_close(dd->fd) ;
}
