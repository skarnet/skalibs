/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/env.h>

char const *env_get2 (char const *const *envp, char const *s)
{
  unsigned int i ;
  unsigned int len ;

  if (!s) return 0 ;
  len = str_len(s) ;
  for (i = 0 ; envp[i] ; ++i)
    if (str_start(envp[i], s)
     && (envp[i][len] == '='))
      return envp[i] + len + 1 ;
  return 0 ;
}
