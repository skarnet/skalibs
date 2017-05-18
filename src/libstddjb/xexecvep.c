/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xexecvep (char const *file, char const *const *argv, char const *const *envp, char const *path)
{
  execvep(file, argv, envp, path) ;
  strerr_dieexec(111, file) ;
}
