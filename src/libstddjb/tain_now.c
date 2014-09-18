/* ISC license. */

/* MT-unsafe */

#include <skalibs/config.h>
#include <skalibs/sysdeps.h>
#include <skalibs/tai.h>

#ifdef SKALIBS_FLAG_USEMON
# ifndef SKALIBS_HASCLOCKMON
#  undef SKALIBS_FLAG_USEMON
#  warning "SKALIBS_FLAG_USEMON set but SKALIBS_HASCLOCKMON not found. Clearing SKALIBS_FLAG_USEMON."
# endif
#endif


#ifdef SKALIBS_FLAG_USEMON

static tain_t offset ;

int tain_init ()
{
  return tain_clockmon_init(&offset) ;
}

int tain_now (tain_t *a)
{
  static int initted = 0 ;
  if (!initted)
  {
    if (!tain_clockmon_init(&offset)) return 0 ;
    initted = 1 ;
  }
  return tain_clockmon(a, &offset) ;
}

#else

int tain_init ()
{
  return 1 ;
}

int tain_now (tain_t *a)
{
  return tain_sysclock(a) ;
}

#endif
