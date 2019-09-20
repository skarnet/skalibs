/* ISC license. */

#include <sys/random.h>

int main (void)
{
  char buf[4] ;
  if (getrandom(buf, 4, GRND_NONBLOCK) < 0) return 1 ;
  return 0 ;
}
