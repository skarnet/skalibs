/* ISC license. */

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <skalibs/uint64.h>
#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>
#include <skalibs/djbunix.h>

int openwritevnclose_suffix_internal (char const *fn, siovec_t const *v, unsigned int n, uint64 *dev, uint64 *ino, int dosync, char const *suffix)
{
  uint64 tmpdev, tmpino ;
  unsigned int len = str_len(fn) ;
  unsigned int suffixlen = str_len(suffix) ;
  char tmp[len + suffixlen + 1] ;
  byte_copy(tmp, len, fn) ;
  byte_copy(tmp + len, suffixlen + 1, suffix) ;
  if (!openwritevnclose_unsafe_internal(tmp, v, n, dev ? &tmpdev : 0, ino ? &tmpino : 0, dosync)) return 0 ;	
  if (rename(tmp, fn) < 0)
  {
    register int e = errno ;
    unlink(tmp) ;
    errno = e ;
    return 0 ;
  }
  if (dev) *dev = tmpdev ;
  if (ino) *ino = tmpino ;
  return 1 ;
}
