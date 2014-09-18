/* ISC license. */

#include <skalibs/tai.h>

unsigned int timestamp_fmt (char *s, tain_t const *a)
{
  *s = '@' ;
  return 1 + tain_fmt(s+1, a) ;
}
