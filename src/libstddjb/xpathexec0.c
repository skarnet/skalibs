/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xpathexec0 (char const *const *argv)
{
  pathexec0(argv) ;
  strerr_dieexec(111, argv[0]) ;
}
