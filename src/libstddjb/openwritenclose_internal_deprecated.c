/* ISC license. */

#include <skalibs/devino.h>
#include <skalibs/djbunix.h>

int openwritenclose_internal (char const *fn, char const *s, size_t n, dev_t *dev, ino_t *ino, int dosync)
{
  devino di ;
  if (!openwritenclose5(fn, s, n, dev || ino ? &di : 0, !!dosync)) return 0 ;
  if (dev) *dev = di.dev ;
  if (ino) *ino = di.ino ;
  return 1 ;
}
