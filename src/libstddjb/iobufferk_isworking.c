/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSPLICE

#include <skalibs/nonposix.h>
#include <errno.h>
#include <fcntl.h>
#include <skalibs/iobuffer.h>

int iobufferk_isworking (iobufferk_ref k)
{
 /* for now splice() with a length of 0 returns 0 no matter what, so this */
 /* test is useless. splice() should test the underlying filesystems even */
 /* if the length is 0. */

# if 0

  register int e = errno ;
  if (splice(k->fd[0], 0, k->p[1], 0, 0, 0) < 0) goto no ;
  if (splice(k->p[0], 0, k->fd[1], 0, 0, 0) < 0) goto no ;
  errno = e ;
  return 1 ;
 no:
  errno = e ;
  return 0 ;

# else

  (void)k ;
  return 1 ;

# endif
}

#else

#include <skalibs/iobuffer.h>

int iobufferk_isworking (iobufferk_ref k)
{
  (void)k ;
  return 0 ;
}

#endif

