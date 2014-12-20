/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSPLICE

#include <sys/stat.h>
#include <fcntl.h>
#include <skalibs/djbunix.h>
#include <skalibs/iobuffer.h>

static int iobufferk_init_0 (iobufferk *k)
{
  register int fd = open_write("/dev/null") ;
  if (fd < 0) return 0 ;
  if (coe(fd) < 0)
  {
    fd_close(fd) ;
    return 0 ;
  }
  k->p[0] = -1 ;
  k->p[1] = fd ;
  return 1 ;
}

static int iobufferk_nofd (iobufferk *k)
{
  k->p[0] = k->p[1] = -1 ;
  return 1 ;
}

static int iobufferk_init_3 (iobufferk *k)
{
  return (pipenbcoe(k->p) >= 0) ;
}

static iobufferk_io_func_t_ref iobufferk_init_f[4] =
{
  &iobufferk_init_0, &iobufferk_nofd, &iobufferk_nofd, &iobufferk_init_3
} ;

int iobufferk_init (iobufferk *k, int fdin, int fdout)
{
  iobufferk tmp ;
  struct stat st ;
  register int r ;
  if (fstat(fdin, &st) < 0) return 0 ;
  r = fcntl(fdin, F_GETFL) ;
  if (r < 0) return 0 ;
  tmp.type = !S_ISFIFO(st.st_mode) ;
  tmp.nb = !!(r & O_NONBLOCK) ;
  if (fstat(fdout, &st) < 0) return 0 ;
  r = fcntl(fdout, F_GETFL) ;
  if (r < 0) return 0 ;
  tmp.type |= (!S_ISFIFO(st.st_mode) << 1) ;
  tmp.nb |= (r & O_NONBLOCK) ? 2 : 0 ;
  tmp.fd[0] = fdin ;
  tmp.fd[1] = fdout ;
  tmp.n = 0 ;
  if (!(*iobufferk_init_f[tmp.type])(&tmp)) return 0 ;
  *k = tmp ;
  return 1 ;
}

#else

#include <errno.h>
#include <skalibs/iobuffer.h>

int iobufferk_init (iobufferk *k, int fdin, int fdout)
{
  (void)k ;
  (void)fdin ;
  (void)fdout ;
  return (errno = ENOSYS, 0) ;
}

#endif
