/* ISC license. */

#include <sys/types.h>
#include <signal.h>
#include <time.h>

int main (void)
{
  timer_t blah ;
  if (timer_create(CLOCK_REALTIME, 0, &blah) < 0) return 111 ;
  return 0 ;
}
