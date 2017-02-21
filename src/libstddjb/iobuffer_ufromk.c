/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSPLICE

#include <sys/types.h>
#include <skalibs/iobuffer.h>

int iobuffer_ufromk (iobufferu *u, iobufferk *k)
{
  int in = u->b[0].fd ;
  u->b[0].fd = k->p[0] ;
  while (k->n)
  {
    ssize_t r = iobufferu_fill(u) ;
    if (r <= 0) goto err ;
    k->n -= r ;
  }
  u->b[0].fd = in ;
  return 1 ;

 err:
  u->b[0].fd = in ;
  return 0 ;
}

#else

#include <errno.h>
#include <skalibs/iobuffer.h>

int iobuffer_ufromk (iobufferu *u, iobufferk *k)
{
  (void)u ;
  (void)k ;
  return (errno = ENOSYS, 0) ;
}

#endif
