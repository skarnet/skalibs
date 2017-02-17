/* ISC license. */

#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <skalibs/types.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>
#include <skalibs/random.h>
#include <skalibs/unix-transactional.h>

int openwritenclose_devino_tmp (char const *fn, char const *s, size_t len, dev_t *dev, ino_t *ino, stralloc *tmp)
{
  dev_t tmpdev ;
  ino_t tmpino ;
  size_t base = tmp->len ;
  if (!stralloc_cats(tmp, fn)) return 0 ;
  if (!random_sauniquename(tmp, 8)) goto fail ;
  if (!stralloc_0(tmp)) goto fail ;
  if (!openwritenclose_unsafe_devino_sync(tmp->s + base, s, len, &tmpdev, &tmpino)) goto fail ;
  if (rename(tmp->s + base, fn) < 0)
  {
    int e = errno ;
    unlink(tmp->s + base) ;
    errno = e ;
    goto fail ;
  }
  tmp->len = base ;
  *dev = tmpdev ;
  *ino = tmpino ;
  return 1 ;

 fail:
  tmp->len = base ;
  return 0 ;
}
