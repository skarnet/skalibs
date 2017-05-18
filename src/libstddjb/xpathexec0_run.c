/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xpathexec0_run (char const *const *argv, char const *const *envp)
{
  pathexec0_run(argv, envp) ;
  strerr_dieexec(111, argv[0]) ;
}
