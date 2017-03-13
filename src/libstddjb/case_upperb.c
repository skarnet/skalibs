/* ISC license. */

#include <skalibs/bytestr.h>

void case_upperb (char *s, size_t len)
{
  unsigned char const d = 'a' - 'A' ;
  while (len--)
  {
    if (('a' <= *s) && (*s <= 'z')) *s -= d ;
    ++s ;
  }
}
