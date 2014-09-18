/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <skalibs/djbunix.h>

int fd_chdir (int d)
{
  register int r ;
  do
    r = fchdir(d) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
