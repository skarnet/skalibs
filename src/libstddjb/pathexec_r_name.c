/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/env.h>
#include <skalibs/djbunix.h>

void pathexec_r_name (char const *file, char const *const *argv, char const *const *envp, size_t envlen, char const *modifs, size_t modiflen)
{
  size_t n = envlen + 1 + byte_count(modifs, modiflen, '\0') ;
  char const *v[n] ;
  if (env_merge(v, n, envp, envlen, modifs, modiflen))
    pathexec_run(file, argv, v) ;
}
