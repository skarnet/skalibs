/* ISC license. */

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <skalibs/djbunix.h>

int fd_chown (int fd, unsigned int uid, unsigned int gid)
{
  register int r ;
  do
    r = fchown(fd, (uid_t)uid, (gid_t)gid) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
