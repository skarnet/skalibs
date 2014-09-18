/* ISC license. */

#include <skalibs/tai.h>

int timestamp (char *s)
{
  tain_t now ;
  return timestamp_r(s, &now) ;
}
