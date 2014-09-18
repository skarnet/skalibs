/* ISC license. */

#include <skalibs/bytestr.h>

void case_upperb (register char *s, unsigned int len)
{
  register unsigned char const d = 'a' - 'A' ;
  while (len--)
  {
    if (('a' <= *s) && (*s <= 'z')) *s -= d ;
    ++s ;
  }
}
