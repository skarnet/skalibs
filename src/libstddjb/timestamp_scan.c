/* ISC license. */

#include <skalibs/tai.h>

unsigned int timestamp_scan (char const *s, tain_t *a)
{
  register unsigned int r ;
  if (*s != '@') return 0 ;
  r = tain_scan(s+1, a) ;
  return r ? r+1 : 0 ;
}
