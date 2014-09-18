/* ISC license. */

#include <skalibs/djbunix.h>

void pathexec_r (char const *const *argv, char const *const *envp, unsigned int envlen, char const *modifs, unsigned int modiflen)
{
  pathexec_r_name(argv[0], argv, envp, envlen, modifs, modiflen) ;
}
