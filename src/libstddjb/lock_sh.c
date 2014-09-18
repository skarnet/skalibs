/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASFLOCK

#include <skalibs/nonposix.h>
#include <errno.h>
#include <sys/file.h>
#include <skalibs/djbunix.h>

int lock_sh (int fd)
{
  register int r ;
  do
    r = flock(fd, LOCK_SH) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}

#else

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <skalibs/djbunix.h>

int lock_sh (int fd)
{
  register int r ;
  do
    r = lockf(fd, F_LOCK, 0) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}

#endif
