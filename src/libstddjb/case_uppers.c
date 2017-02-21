/* ISC license. */

#include <skalibs/bytestr.h>

void case_uppers (char *s)
{
  unsigned char const d = 'a' - 'A' ;
  while (*s)
  {
    if (('a' <= *s) && (*s <= 'z')) *s -= d ;
    ++s ;
  }
}
