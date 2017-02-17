/* ISC license. */

#include <sys/types.h>
#include <skalibs/types.h>
#include <skalibs/stralloc.h>
#include <skalibs/unix-transactional.h>

int openwritenclose_tmp (char const *fn, char const *s, size_t len, stralloc *tmp)
{
  dev_t dev ;
  ino_t ino ;
  return openwritenclose_devino_tmp(fn, s, len, &dev, &ino, tmp) ;
}
