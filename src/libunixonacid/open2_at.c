/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASOPENAT

#ifndef _ATFILE_SOURCE
#define _ATFILE_SOURCE
#endif

#include <skalibs/nonposix.h>
#include <fcntl.h>
#include <skalibs/unix-transactional.h>

int open2_at (int dirfd, char const *file, int flags)
{
  return openat(dirfd, file, flags) ;
}

#else

#include <sys/types.h>
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
  if (fd_chdir(dirfd) < 0)
  {
    int e = errno ;
    fd_close(fdhere) ;
    errno = e ;
    return -1 ;
  }
  fd = open2(file, flags) ;
  if (fd < 0)
  {
    int e = errno ;
    fd_chdir(fdhere) ;
    fd_close(fdhere) ;
    errno = e ;
    return -1 ;
  }
  if (fd_chdir(fdhere) < 0)
  {
    int e = errno ;
    fd_close(fdhere) ;
    errno = e ;
    return -1 ;
  }
  return fd ;
}

#endif
