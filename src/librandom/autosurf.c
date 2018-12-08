/* ISC license. */

#include <skalibs/random.h>
#include <skalibs/surf.h>

void autosurf (char *s, size_t n)
{
  static SURFSchedule ctx = SURFSCHEDULE_ZERO ;
  static int need4seed = 1 ;
  if (need4seed)
  {
    char tmp[160] ;
    random_makeseed(tmp) ;
    surf_init(&ctx, tmp) ;
    need4seed = 0 ;
  }
  return surf(&ctx, s, n) ;
}
