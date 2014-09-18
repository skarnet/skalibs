/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/env.h>
#include <skalibs/djbunix.h>

static stralloc plus = STRALLOC_ZERO ;

int pathexec_env (char const *s, char const *t) /* historic, bad name */
{
  return env_addmodif(&plus, s, t) ;
}

void pathexec_fromenv (char const *const *argv, char const *const *envp, unsigned int envlen)
{
  pathexec_r(argv, envp, envlen, plus.s, plus.len) ;
}
