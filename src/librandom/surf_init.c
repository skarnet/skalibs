/* ISC license. */

#include <skalibs/surf.h>

void surf_init (SURFSchedule_ref ctx)
{
  char s[160] ;
  surf_makeseed(s) ;
  surf_sinit(ctx, s) ;
}
