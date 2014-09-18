/* ISC license. */

#include <skalibs/bytestr.h>

void case_lowers (register char *s)
{
  register unsigned char const d = 'a' - 'A' ;
  while (*s)
  {
    if (('A' <= *s) && (*s <= 'Z')) *s += d ;
    ++s ;
  }
}
