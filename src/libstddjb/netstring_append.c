/* ISC license. */

#include <sys/types.h>
#include <skalibs/uint64.h>
#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>
#include <skalibs/netstring.h>

int netstring_appendb (stralloc *sa, char const *s, size_t len)
{
  char fmt[UINT64_FMT] ;
  size_t n = uint64_fmt(fmt, len) ;
  if (!stralloc_readyplus(sa, len + n + 2)) return 0 ;
  fmt[n] = ':' ;
  byte_copy(sa->s + sa->len, n+1, fmt) ;
  byte_copy(sa->s + sa->len + n+1, len, s) ;
  sa->s[sa->len + n+1 + len] = ',' ;
  sa->len += n + 2 + len ;
  return 1 ;
}
