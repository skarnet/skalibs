/* ISC license. */

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <skalibs/djbunix.h>

#define SUFFIX ":skalibs-openwritenclose:XXXXXX"

int openwritenclose_internal (char const *fn, char const *s, size_t n, dev_t *dev, ino_t *ino, int dosync)
{
  dev_t tmpdev ;
  ino_t tmpino ;
  size_t fnlen = strlen(fn) ;
  int fd ;
  char tmp[fnlen + sizeof(SUFFIX)] ;
  memcpy(tmp, fn, fnlen) ;
  memcpy(tmp + fnlen, SUFFIX, sizeof(SUFFIX)) ;
  fd = mkstemp(tmp) ;
  if (fd < 0) return 0 ;
  if (!writenclose_unsafe_internal(fd, s, n, dev ? &tmpdev : 0, ino ? &tmpino : 0, dosync)) goto failclose ;
  if (rename(tmp, fn) < 0) goto fail ;
  if (dev) *dev = tmpdev ;
  if (ino) *ino = tmpino ;
  return 1 ;

 failclose:
  fd_close(fd) ;
 fail:
  {
    int e = errno ;
    unlink(tmp) ;
    errno = e ;
  }
  return 0 ;
}
