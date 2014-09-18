/* ISC license. */

#include <skalibs/uint.h>
#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>
#include <skalibs/stralloc.h>
#include <skalibs/netstring.h>

int netstring_appendv (stralloc *sa, siovec_t const *v, unsigned int n)
{
  char fmt[UINT_FMT] ;
  unsigned int len = 0, pos ;
  register unsigned int i = 0 ;
  for (; i < n ; i++) len += v[i].len ;
  pos = uint_fmt(fmt, len) ;
  if (!stralloc_readyplus(sa, len + pos + 2)) return 0 ;
  fmt[pos] = ':' ;
  byte_copy(sa->s + sa->len, pos+1, fmt) ;
  sa->len += pos+1 ;
  for (i = 0 ; i < n ; i++)
  {
    byte_copy(sa->s + sa->len, v[i].len, v[i].s) ;
    sa->len += v[i].len ;
  }
  sa->s[sa->len++] = ',' ;
  return 1 ;
}
