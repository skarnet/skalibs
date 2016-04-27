/* ISC license. */

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main (void)
{
  struct timespec foo[2] = { { .tv_sec = 0, .tv_nsec = 0 }, { .tv_sec = 0, .tv_nsec = 0 } } ;
  futimens(0, foo) ;
  return 0 ;
}
