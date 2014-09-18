/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSPLICE

#include <skalibs/nonposix.h>
#include <fcntl.h>
#include <errno.h>
#include <skalibs/iobuffer.h>

static int iobufferk_tee (iobufferk_ref k)
{
  register int r = tee(k->fd[0], k->fd[1], IOBUFFERK_SIZE - k->n, k->nb & 1 ? SPLICE_F_NONBLOCK : 0) ;
  if (r > 0) k->n += r ;
  return r ;
}

static int iobufferk_splice (iobufferk_ref k)
{
  register int r = splice(k->fd[0], 0, k->fd[1], 0, IOBUFFERK_SIZE, k->nb ? SPLICE_F_NONBLOCK : 0) ;
  if (r > 0) k->n += r ;
  if ((r < 0) && (errno == EINVAL)) errno = ENOSYS ;
  return r ;
}

static int iobufferk_fill_3 (iobufferk_ref k)
{
  register int r = splice(k->fd[0], 0, k->p[1], 0, IOBUFFERK_SIZE - k->n, k->nb & 1 ? SPLICE_F_NONBLOCK : 0) ;
  if (r > 0) k->n += r ;
  if ((r < 0) && (errno == EINVAL)) errno = ENOSYS ;
  return r ;
}

iobufferk_io_func_t_ref const iobufferk_fill_f[4] =
{
  &iobufferk_tee, &iobufferk_splice, &iobufferk_splice, &iobufferk_fill_3
} ;

#else

#include <skalibs/iobuffer.h>

iobufferk_io_func_t_ref const iobufferk_fill_f[4] =
{
  &iobufferk_nosys, &iobufferk_nosys, &iobufferk_nosys, &iobufferk_nosys
} ;

#endif
