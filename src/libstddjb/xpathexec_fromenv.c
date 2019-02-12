/* ISC license. */

#include <errno.h>

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

void xpathexec_fromenv (char const *const *argv, char const *const *envp, size_t envlen)
{
  pathexec_fromenv(argv, envp, envlen) ;
  strerr_dieexec(errno == ENOENT ? 127 : 126, argv[0]) ;
}
