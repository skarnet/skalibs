/* ISC license. */

#include <skalibs/devino.h>
#include <skalibs/djbunix.h>

int openwritenclose_unsafe_internal (char const *fn, char const *s, size_t len, dev_t *dev, ino_t *ino, int dosync)
{
  devino di ;
  if (!openwritenclose_unsafe5(fn, s, len, dev || ino ? &di : 0, !!dosync)) return 0 ;
  if (dev) *dev = di.dev ;
  if (ino) *ino = di.ino ;
  return 1 ;
}
