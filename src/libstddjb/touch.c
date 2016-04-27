/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASFUTIMENS

#include <time.h>
#include <sys/stat.h>
#include <skalibs/djbunix.h>

int touch (char const *file)
{
  register int fd = open_create(file) ;
  if (fd < 0) return 0 ;
  if (futimens(fd, 0) < 0) return 0 ;
  fd_close(fd) ;
  return 1 ;
}

#else
#ifdef SKALIBS_HASFUTIMES

#include <skalibs/nonposix.h>
#include <sys/time.h>
#include <skalibs/djbunix.h>

int touch (char const *file)
{
  register int fd = open_create(file) ;
  if (fd < 0) return 0 ;
  if (futimes(fd, 0) < 0) return 0 ;
  fd_close(fd) ;
  return 1 ;
}

#else

#include <sys/time.h>
#include <skalibs/djbunix.h>

int touch (char const *file)
{
  register int fd = open_create(file) ;
  if (fd < 0) return 0 ;
  fd_close(fd) ;
  if (utimes(file, 0) < 0) return 0 ;
  return 1 ;
}

#endif
#endif
