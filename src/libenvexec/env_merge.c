/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/env.h>

size_t env_merge (char const **v, size_t vmax, char const *const *envp, size_t envlen, char const *modifs, size_t modiflen)
{
  return env_mergen(v, vmax, envp, envlen, modifs, modiflen, byte_count(modifs, modiflen, '\0')) ;
}
