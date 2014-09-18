/* ISC license. */

#include <skalibs/bytestr.h>

void case_lowerb (register char *s, unsigned int len)
{
  register unsigned char const d = 'a' - 'A' ;
  while (len--)
  {
    if (('A' <= *s) && (*s <= 'Z')) *s += d ;
    ++s ;
  }
}
