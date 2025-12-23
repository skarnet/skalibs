/* ISC license. */

#include <unistd.h>

#include <skalibs/strerr.h>
#include <skalibs/djbunix.h>

void fd_sanitize (void)
{
  if (!fd_ensure_open(2, 1)) _exit(111) ;
  if (!fd_ensure_open(1, 1)) strerr_diefu3sys(111, "ensure std", "out", " is open") ;
  if (!fd_ensure_open(0, 0)) strerr_diefu3sys(111, "ensure std", "in",  " is open") ;
}
