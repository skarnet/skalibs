/* ISC license. */

#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <skalibs/djbunix.h>

int openwritevnclose_suffix_internal (char const *fn, struct iovec const *v, unsigned int n, dev_t *dev, ino_t *ino, int dosync, char const *suffix)
{
  dev_t tmpdev ;
  ino_t tmpino ;
  size_t len = strlen(fn) ;
  size_t suffixlen = strlen(suffix) ;
  char tmp[len + suffixlen + 1] ;
  memcpy(tmp, fn, len) ;
  memcpy(tmp + len, suffix, suffixlen + 1) ;
  if (!openwritevnclose_unsafe_internal(tmp, v, n, dev ? &tmpdev : 0, ino ? &tmpino : 0, dosync)) return 0 ;	
  if (rename(tmp, fn) < 0)
  {
    int e = errno ;
    unlink(tmp) ;
    errno = e ;
    return 0 ;
  }
  if (dev) *dev = tmpdev ;
  if (ino) *ino = tmpino ;
  return 1 ;
}
