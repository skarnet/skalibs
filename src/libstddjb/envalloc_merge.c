/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/env.h>
#include <skalibs/genalloc.h>
#include <skalibs/envalloc.h>

int envalloc_merge (genalloc *v, char const *const *envp, unsigned int envlen, char const *modifs, unsigned int modiflen)
{
  unsigned int n = envlen + 1 + byte_count(modifs, modiflen, '\0') ;
  if (!genalloc_readyplus(char const *, v, n)) return 0 ;
  n = env_merge(genalloc_s(char const *, v) + genalloc_len(char const *, v), n, envp, envlen, modifs, modiflen) ;
  genalloc_setlen(char const *, v, genalloc_len(char const *, v) + n) ;
  return 1 ;
}
