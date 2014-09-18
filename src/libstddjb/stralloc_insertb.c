/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>

int stralloc_insertb (stralloc *sa, unsigned int offset, char const *s, unsigned int n)
{
  if (offset > sa->len) return (errno = EINVAL, 0) ;
  if (!stralloc_readyplus(sa, n)) return 0 ;
  byte_copyr(sa->s + offset + n, sa->len - offset, sa->s + offset) ;
  sa->len += n ;
  byte_copyr(sa->s + offset, n, s) ;
  return 1 ;
}
