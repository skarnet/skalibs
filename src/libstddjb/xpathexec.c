/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xpathexec (char const *const *argv)
{
  pathexec(argv) ;
  strerr_dieexec(111, argv[0]) ;
}
