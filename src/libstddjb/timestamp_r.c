/* ISC license. */

#include <skalibs/tai.h>

int timestamp_r (char *s, tain_t *stamp)
{
  if (!tain_sysclock(stamp)) return 0 ;
  timestamp_fmt(s, stamp) ;
  return 1 ;
}
