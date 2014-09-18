/* ISC license. */

#include <unistd.h>
#include <skalibs/djbunix.h>

void pathexec0_run (char const *const *argv, char const *const *envp)
{
  if (!argv[0]) _exit(0) ;
  pathexec_run(argv[0], argv, envp) ;
}
