/* ISC license. */

#include <skalibs/tai.h>
#include <skalibs/djbtime.h>

int localtmn_from_sysclock (localtmn_t_ref l, tain_t const *a, int tz)
{
  struct tm t ;
  if (!localtm_from_sysclock(&t, a->sec.x, tz)) return 0 ;
  l->tm = t ;
  l->nano = a->nano ;
  return 1 ;
}
