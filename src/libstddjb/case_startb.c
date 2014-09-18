/* ISC license. */

#include <skalibs/bytestr.h>

int case_startb (register char const *s, unsigned int slen, register char const *t)
{
  register unsigned int tlen = str_len(t) ;
  return slen < tlen ? 0 : !case_diffb(s, tlen, t) ;
}
