/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xpathexec_r (char const *const *argv, char const *const *envp, size_t envlen, char const *modifs, size_t modiflen)
{
  pathexec_r(argv, envp, envlen, modifs, modiflen) ;
  strerr_dieexec(111, argv[0]) ;
}
