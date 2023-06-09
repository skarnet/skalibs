/* ISC license. */

#include <skalibs/devino.h>
#include <skalibs/djbunix.h>

int openwritevnclose_unsafe_internal (char const *fn, struct iovec const *v, unsigned int vlen, dev_t *dev, ino_t *ino, int dosync)
{
  devino di ;
  if (!openwritevnclose_unsafe5(fn, v, vlen, dev || ino ? &di : 0, !!dosync)) return 0 ;
  if (dev) *dev = di.dev ;
  if (ino) *ino = di.ino ;
  return 1 ;
}
