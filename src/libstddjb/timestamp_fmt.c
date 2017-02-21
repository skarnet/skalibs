/* ISC license. */

#include <sys/types.h>
#include <skalibs/tai.h>

size_t timestamp_fmt (char *s, tain_t const *a)
{
  *s = '@' ;
  return 1 + tain_fmt(s+1, a) ;
}
