/* ISC license. */

/* MT-unsafe */

#include <sys/types.h>
#include <skalibs/types.h>
#include <skalibs/skamisc.h>
#include <skalibs/unix-transactional.h>

int openwritenclose_devino (char const *fn, char const *s, size_t len, dev_t *dev, ino_t *ino)
{
  return openwritenclose_devino_tmp(fn, s, len, dev, ino, &satmp) ;
}
