/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASFLOCK

#include <skalibs/nonposix.h>
#include <errno.h>
#include <sys/file.h>
#include <skalibs/djbunix.h>

int lock_shnb (int fd)
{
  register int r ;
  do
    r = flock(fd, LOCK_SH | LOCK_NB) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}

#else

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <skalibs/djbunix.h>

int lock_shnb (int fd)
{
  register int r ;
  do
    r = lockf(fd, F_TLOCK, 0) ;
  while ((r == -1) && (errno == EINTR)) ;
  if ((r == -1) && (errno == EACCES)) errno = EAGAIN ;
  return r ;
}

#endif
