/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASOPENAT

#ifndef _ATFILE_SOURCE
#define _ATFILE_SOURCE
#endif

#include <skalibs/nonposix.h>

#include <errno.h>

#include <skalibs/fcntl.h>
#include <skalibs/unix-transactional.h>

int open3_at (int dirfd, char const *file, int flags, unsigned int mode)
{
  int fd ;
  do fd = openat(dirfd, file, flags, mode) ; /* all systems that support openat() have O_CLOEXEC */
  while (fd == -1 && errno == EINTR) ;
  return fd ;
}

#else

#include <sys/stat.h>
#include <errno.h>

#include <skalibs/fcntl.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

int open3_at (int dirfd, char const *file, int flags, unsigned int mode)
{
  int fd ;
  int fdhere = open_read(".") ;
  if (fdhere < 0) return -1 ;
  if (fd_chdir(dirfd) < 0) goto errclose ;
  fd = open3(file, flags, mode) ;
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
