/* ISC license. */

#include <errno.h>

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xpathexec0_run (char const *const *argv, char const *const *envp)
{
  pathexec0_run(argv, envp) ;
  strerr_dieexec(errno == ENOENT ? 127 : 126, argv[0]) ;
}
