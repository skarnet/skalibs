/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/env.h>
#include <skalibs/djbunix.h>

void pathexec_run (char const *file, char const *const *argv, char const *const *envp)
{
  char const *path = env_get("PATH") ;
  if (!path) path = SKALIBS_DEFAULTPATH ;
  execvep(file, argv, envp, path) ;
}
