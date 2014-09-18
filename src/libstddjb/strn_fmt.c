/* ISC license. */

#include <skalibs/fmtscan.h>
#include <skalibs/uint.h>

unsigned int strn_fmt (char *blah, register char const *s, unsigned int len)
{
  register char *d = blah ;
  unsigned int i ;
  for (i = 0 ; i < len ; i++)
    if ((s[i] >= 32) && ((unsigned char)s[i] < 127)) *d++ = s[i] ;
    else
    {
      *d++ = '\\' ;
      *d++ = '0' ;
      *d++ = 'x' ;
      if ((unsigned char)s[i] < 16) *d++ = '0' ;
      d += uint_xfmt(d, (unsigned char)s[i]) ;
    }
  return d - blah ;
}
