/* ISC license. */

/* MT-unsafe */

#include <skalibs/tai.h>

#if defined(SKALIBS_HASCLOCKRT) && (defined(SKALIBS_HASCLOCKMON) || defined(SKALIBS_HASCLOCKBOOT))

#include <time.h>

#ifdef SKALIBS_HASCLOCKMON
# define SKALIBS_STOPWATCH CLOCK_MONOTONIC
#else
# define SKALIBS_STOPWATCH CLOCK_BOOTTIME
#endif

static tain_t offset ;

static int tain_now_stopwatch (tain_t *a)
{
  return tain_stopwatch_read(a, SKALIBS_STOPWATCH, &offset) ;
}

void tain_now_set_stopwatch (void)
{
  if (!tain_stopwatch_init(SKALIBS_STOPWATCH, &offset)) return ;
  tain_now = &tain_now_stopwatch ;
}

#else

void tain_now_set_stopwatch (void)
{
}

#endif
