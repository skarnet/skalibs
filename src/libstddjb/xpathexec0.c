/* ISC license. */

#include <errno.h>

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xpathexec0 (char const *const *argv)
{
  pathexec0(argv) ;
  strerr_dieexec(errno == ENOENT ? 127 : 126, argv[0]) ;
}
