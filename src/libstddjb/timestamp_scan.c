/* ISC license. */

#include <sys/types.h>
#include <skalibs/tai.h>

size_t timestamp_scan (char const *s, tain_t *a)
{
  size_t r ;
  if (*s != '@') return 0 ;
  r = tain_scan(s+1, a) ;
  return r ? r+1 : 0 ;
}
