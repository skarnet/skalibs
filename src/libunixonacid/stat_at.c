/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASOPENAT

#ifndef _ATFILE_SOURCE
#define _ATFILE_SOURCE
#endif

#include <skalibs/nonposix.h>

#include <sys/stat.h>

#include <skalibs/fcntl.h>
#include <skalibs/unix-transactional.h>

int stat_at (int dirfd, char const *file, struct stat *st)
{
  return fstatat(dirfd, file, st, 0) ;
}

int lstat_at (int dirfd, char const *file, struct stat *st)
{
  return fstatat(dirfd, file, st, AT_SYMLINK_NOFOLLOW) ;
}

#else

 /* OpenBSD plz. lstat() is POSIX. */
#include <skalibs/nonposix.h>

#include <sys/stat.h>
#include <errno.h>

#include <skalibs/fcntl.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

static int fstat_at (int dirfd, char const *file, struct stat *st, int (*dostat)(char const *, struct stat *))
{
  int r ;
  int fdhere = open_read(".") ;
  if (fdhere < 0) return -1 ;
  if (fd_chdir(dirfd) < 0)
  {
    fd_close(fdhere) ;
    return -1 ;
  }
  r = (*dostat)(file, st) ;
  if (r < 0)
  {
    int e = errno ;
    fd_chdir(fdhere) ;
    fd_close(fdhere) ;
    errno = e ;
    return -1 ;
  }
  if (fd_chdir(fdhere) < 0)
  {
    fd_close(fdhere) ;
    return -1 ;
  }
  fd_close(fdhere) ;
  return r ;
}

int stat_at (int dirfd, char const *file, struct stat *st)
{
  return fstat_at(dirfd, file, st, &stat) ;
}

int lstat_at (int dirfd, char const *file, struct stat *st)
{
  return fstat_at(dirfd, file, st, &lstat) ;
}

#endif
