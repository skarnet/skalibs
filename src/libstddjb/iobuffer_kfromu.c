/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSPLICE

#include <skalibs/nonposix.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <skalibs/buffer.h>
#include <skalibs/iobuffer.h>
#include <skalibs/siovec.h>

int iobuffer_kfromu (iobufferk *k, iobufferu *u)
{
  struct iovec v[2] ;
  ssize_t r ;
  buffer_rpeek(&u->b[0], v) ;
  r = vmsplice(k->p[1], v, 2, 0) ;
  if (r < 0) return 0 ;
  k->n += r ;
  buffer_rseek(&u->b[0], r) ;
  u->b[1].c.p = u->b[0].c.p ;
  return iobufferu_isempty(u) ;
}

#else

#include <errno.h>
#include <skalibs/iobuffer.h>

int iobuffer_kfromu (iobufferk *k, iobufferu *u)
{
  (void)k ;
  (void)u ;
  return (errno = ENOSYS, 0) ;
}

#endif
