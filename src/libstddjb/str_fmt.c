/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/fmtscan.h>

unsigned int str_fmt (register char *d, char const *s)
{
  return strn_fmt(d, s, str_len(s)) ;
}
