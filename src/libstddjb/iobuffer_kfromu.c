/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSPLICE

#include <skalibs/nonposix.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <skalibs/buffer.h>
#include <skalibs/iobuffer.h>
#include <skalibs/siovec.h>

int iobuffer_kfromu (iobufferk_ref k, iobufferu_ref u)
{
  struct iovec iov[2] ;
  siovec_t v[2] ;
  int r ;
  buffer_rpeek(&u->b[0], v) ;
  iovec_from_siovec(iov, v, 2) ;
  r = vmsplice(k->p[1], iov, 2, 0) ;
  if (r < 0) return 0 ;
  k->n += r ;
  buffer_rseek(&u->b[0], (unsigned int)r) ;
  u->b[1].c.p = u->b[0].c.p ;
  return iobufferu_isempty(u) ;
}

#else

#include <errno.h>
#include <skalibs/iobuffer.h>

int iobuffer_kfromu (iobufferk_ref k, iobufferu_ref u)
{
  (void)k ;
  (void)u ;
  return (errno = ENOSYS, 0) ;
}

#endif
