/* ISC license. */

#include <skalibs/djbunix.h>

void pathexec_r (char const *const *argv, char const *const *envp, size_t envlen, char const *modifs, size_t modiflen)
{
  pathexec_r_name(argv[0], argv, envp, envlen, modifs, modiflen) ;
}
