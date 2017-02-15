/* ISC license. */

#include <sys/types.h>
#include <string.h>
#include <skalibs/bytestr.h>

int case_startb (register char const *s, size_t slen, register char const *t)
{
  size_t tlen = strlen(t) ;
  return slen < tlen ? 0 : !case_diffb(s, tlen, t) ;
}
