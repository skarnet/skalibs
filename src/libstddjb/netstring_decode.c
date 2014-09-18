/* ISC license. */

#include <errno.h>
#include <skalibs/fmtscan.h>
#include <skalibs/netstring.h>
#include <skalibs/stralloc.h>
#include <skalibs/uint.h>

int netstring_decode (stralloc *sa, char const *s, unsigned int len)
{
  unsigned int nlen ;
  register unsigned int pos ;
  if (!len) return 0 ;
  pos = uint_scan(s, &nlen) ;
  if (pos >= len) return (errno = EINVAL, -1) ;
  if (s[pos] != ':') return (errno = EINVAL, -1) ;
  s += pos+1 ; len -= pos+1 ;
  if (len <= nlen) return (errno = EINVAL, -1) ;
  if (s[nlen] != ',') return (errno = EINVAL, -1) ;
  if (!stralloc_catb(sa, s, nlen)) return -1 ;
  return pos + nlen + 2 ;
}
