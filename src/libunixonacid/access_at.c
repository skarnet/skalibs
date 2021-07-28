/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASLINKAT

#ifndef _ATFILE_SOURCE
#define _ATFILE_SOURCE
#endif

#include <skalibs/nonposix.h>

#include <fcntl.h>
#include <unistd.h>

#include <skalibs/unix-transactional.h>

int access_at (int dirfd, char const *file, int amode, unsigned int flag)
{
  return faccessat(dirfd, file, amode, flag ? AT_EACCESS : 0) ;
}

#else

#include <errno.h>
#include <unistd.h>

#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

int access_at (int dirfd, char const *file, int amode, unsigned int flag)
{
  int fdhere ;
  if (getuid() != geteuid() || getgid() != getegid())
    return (errno = ENOSYS, -1) ;
  (void)flag ;
  fdhere = open_read(".") ;
  if (fdhere < 0) return -1 ;
  if (fd_chdir(dirfd) < 0)
  {
    fd_close(fdhere) ;
    return -1 ;
  }
  if (access(file, amode) < 0)
  {
    int e = errno ;
    fd_chdir(fdhere) ;
    fd_close(fdhere) ;
    return (errno = e, -1) ;
  }
  fd_chdir(fdhere) ;
  fd_close(fdhere) ;
  return 0 ;
}

#endif
