/* ISC license. */

#include <skalibs/devino.h>
#include <skalibs/djbunix.h>

int writenclose_unsafe_internal (int fd, char const *s, size_t len, dev_t *dev, ino_t *ino, int dosync)
{
  devino di ;
  if (!writenclose_unsafe5(fd, s, len, dev || ino ? &di : 0, !!dosync)) return 0 ;
  if (dev) *dev = di.dev ;
  if (ino) *ino = di.ino ;
  return 1 ;
}
