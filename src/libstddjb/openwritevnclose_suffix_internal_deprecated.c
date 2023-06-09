/* ISC license. */

#include <skalibs/devino.h>
#include <skalibs/djbunix.h>

int openwritevnclose_suffix_internal (char const *fn, struct iovec const *v, unsigned int n, dev_t *dev, ino_t *ino, int dosync, char const *suffix)
{
  devino di ;
  if (!openwritevnclose_suffix6(fn, v, n, dev || ino ? &di : 0, !!dosync, suffix)) return 0 ;	
  if (dev) *dev = di.dev ;
  if (ino) *ino = di.ino ;
  return 1 ;
}
