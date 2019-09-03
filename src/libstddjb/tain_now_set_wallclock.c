/* ISC license. */

/* MT-unsafe */

#include <skalibs/tai.h>

void tain_now_set_wallclock (void)
{
  tain_now = &tain_wallclock_read ;
}
