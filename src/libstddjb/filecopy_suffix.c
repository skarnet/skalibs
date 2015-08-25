/* ISC license. */

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <skalibs/bytestr.h>
#include <skalibs/djbunix.h>

int filecopy_suffix (char const *src, char const *dst, unsigned int mode, char const *suffix)
{
  unsigned int dstlen = str_len(dst) ;
  unsigned int suffixlen = str_len(suffix) ;
  char tmp[dstlen + suffixlen + 1] ;
  byte_copy(tmp, dstlen, dst) ;
  byte_copy(tmp + dstlen, suffixlen + 1, suffix) ;
  if (!filecopy_unsafe(src, tmp, mode)) return 0 ;	
  if (rename(tmp, dst) < 0)
  {
    register int e = errno ;
    unlink(tmp) ;
    errno = e ;
    return 0 ;
  }
  return 1 ;
}
