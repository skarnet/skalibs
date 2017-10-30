/* ISC license. */

#include <errno.h>
#include <skalibs/djbunix.h>

void lock_unx (int fd)
{
  int e = errno ;
  lock_un(fd) ;
  errno = e ;
}
