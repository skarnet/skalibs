/* ISC license. */

#include <skalibs/uint64.h>
#include <skalibs/stralloc.h>
#include <skalibs/unix-transactional.h>

int openwritenclose_tmp (char const *fn, char const *s, unsigned int len, stralloc *tmp)
{
  uint64 dev, ino ;
  return openwritenclose_devino_tmp(fn, s, len, &dev, &ino, tmp) ;
}
