/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSPLICE

#include <skalibs/nonposix.h>
#include <fcntl.h>
#include <errno.h>
#include <skalibs/iobuffer.h>

static int iobufferk_flush_0 (iobufferk *k)
{
  while (k->n)
  {
    ssize_t r = splice(k->fd[0], 0, k->p[1], 0, k->n, 0) ;
    if (r < 0) return 0 ;
    else if (!r) break ;
    k->n -= r ;
  }
  return 1 ;
}

static int fakeflush (iobufferk *k)
{
  k->n = 0 ;
  return 1 ;
}

static int iobufferk_flush_3 (iobufferk *k)
{
  while (k->n)
  {
    ssize_t r = splice(k->p[0], 0, k->fd[1], 0, k->n, SPLICE_F_MORE | (k->nb & 2 ? SPLICE_F_NONBLOCK : 0)) ;
    if (r < 0)
    {
      if (errno == EINVAL) errno = ENOSYS ;
      return 0 ;
    }
    else if (!r) return (errno = EPIPE, 0) ;
    k->n -= r ;
  }
  return 1 ;
}

iobufferk_output_func_t_ref const iobufferk_flush_f[4] =
{
  &iobufferk_flush_0, &fakeflush, &fakeflush, &iobufferk_flush_3
} ;

#else

#include <errno.h>
#include <skalibs/iobuffer.h>

static int iobufferk_onosys (iobuffer_k *k)
{
  (void)k ;
  return (errno = ENOSYS, -1) ;
}

iobufferk_output_func_t_ref const iobufferk_flush_f[4] =
{
  &iobufferk_onosys, &iobufferk_onosys, &iobufferk_onosys, &iobufferk_onosys
} ;

#endif
