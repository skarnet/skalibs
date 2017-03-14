/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSPLICE

#include <skalibs/nonposix.h>
#include <fcntl.h>
#include <errno.h>
#include <skalibs/iobuffer.h>

static ssize_t iobufferk_tee (iobufferk *k)
{
  ssize_t r = tee(k->fd[0], k->fd[1], IOBUFFERK_SIZE - k->n, k->nb & 1 ? SPLICE_F_NONBLOCK : 0) ;
  if (r > 0) k->n += r ;
  return r ;
}

static ssize_t iobufferk_splice (iobufferk *k)
{
  ssize_t r = splice(k->fd[0], 0, k->fd[1], 0, IOBUFFERK_SIZE, k->nb ? SPLICE_F_NONBLOCK : 0) ;
  if (r > 0) k->n += r ;
  if ((r < 0) && (errno == EINVAL)) errno = ENOSYS ;
  return r ;
}

static ssize_t iobufferk_fill_3 (iobufferk *k)
{
  ssize_t r = splice(k->fd[0], 0, k->p[1], 0, IOBUFFERK_SIZE - k->n, k->nb & 1 ? SPLICE_F_NONBLOCK : 0) ;
  if (r > 0) k->n += r ;
  if ((r < 0) && (errno == EINVAL)) errno = ENOSYS ;
  return r ;
}

iobufferk_input_func_t_ref const iobufferk_fill_f[4] =
{
  &iobufferk_tee, &iobufferk_splice, &iobufferk_splice, &iobufferk_fill_3
} ;

#else

#include <errno.h>
#include <skalibs/iobuffer.h>

static ssize_t iobufferk_inosys (iobufferk *k)
{
  (void)k ;
  return (errno = ENOSYS, -1) ;
}

iobufferk_input_func_t_ref const iobufferk_fill_f[4] =
{
  &iobufferk_inosys, &iobufferk_inosys, &iobufferk_inosys, &iobufferk_inosys
} ;

#endif
