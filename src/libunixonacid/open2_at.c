/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASOPENAT

#ifndef _ATFILE_SOURCE
#define _ATFILE_SOURCE
#endif

#include <skalibs/nonposix.h>

#include <errno.h>
#include <fcntl.h>

#include <skalibs/unix-transactional.h>

int open2_at (int dirfd, char const *file, int flags)
{
  int fd ;
  do fd = openat(dirfd, file, flags) ;
  while (fd == -1 && errno == EINTR) ;
  return fd ;
}

#else

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

int open2_at (int dirfd, char const *file, int flags)
{
  int fd ;
  int fdhere = open_read(".") ;
  if (fdhere < 0) return -1 ;
  if (fd_chdir(dirfd) < 0) goto errclose ;
  fd = open2(file, flags) ;
  if (fd < 0)
  {
    int e = errno ;
    fd_chdir(fdhere) ;
    errno = e ;
    goto errclose ;
  }
  if (fd_chdir(fdhere) < 0)
  {
    fd_close(fd) ;
    goto errclose ;
  }
  fd_close(fdhere) ;
  return fd ;

 errclose:
  fd_close(fdhere) ;
  return -1 ;
}

#endif
