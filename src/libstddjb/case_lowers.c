/* ISC license. */

#include <skalibs/bytestr.h>

void case_lowers (char *s)
{
  unsigned char const d = 'a' - 'A' ;
  while (*s)
  {
    if (('A' <= *s) && (*s <= 'Z')) *s += d ;
    ++s ;
  }
}
