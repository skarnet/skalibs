/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xpathexec_r_name (char const *file, char const *const *argv, char const *const *envp, size_t envlen, char const *modifs, size_t modiflen)
{
  pathexec_r_name(file, argv, envp, envlen, modifs, modiflen) ;
  strerr_dieexec(111, file) ;
}
