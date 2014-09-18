/* ISC license. */

/* MT-unsafe */

#include <skalibs/uint64.h>
#include <skalibs/skamisc.h>
#include <skalibs/unix-transactional.h>

int openwritenclose_devino (char const *fn, char const *s, unsigned int len, uint64 *dev, uint64 *ino)
{
  return openwritenclose_devino_tmp(fn, s, len, dev, ino, &satmp) ;
}
