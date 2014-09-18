/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <skalibs/djbunix.h>

int fd_move (int to, int from)
{
  register int r ;
  if (to == from) return 0 ;
  do
    r = dup2(from, to) ;
  while ((r == -1) && (errno == EINTR)) ;
  return (r == -1) ? -1 : fd_close(from) ;
}
