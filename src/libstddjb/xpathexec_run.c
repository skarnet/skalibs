/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xpathexec_run (char const *file, char const *const *argv, char const *const *envp)
{
  pathexec_run(file, argv, envp) ;
  strerr_dieexec(111, file) ;
}
