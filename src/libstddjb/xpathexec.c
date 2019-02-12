/* ISC license. */

#include <errno.h>

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xpathexec (char const *const *argv)
{
  pathexec(argv) ;
  strerr_dieexec(errno == ENOENT ? 127 : 126, argv[0]) ;
}
