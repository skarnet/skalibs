/* ISC license. */

#include <skalibs/djbunix.h>

unsigned int wait_reap ()
{
  register unsigned int n = 0 ;
  int wstat ;
  while (wait_nohang(&wstat) > 0) n++ ;
  return n ;
}
