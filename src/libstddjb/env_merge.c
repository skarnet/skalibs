/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/env.h>

unsigned int env_merge (char const **v, unsigned int vmax, char const *const *envp, unsigned int envlen, char const *modifs, unsigned int modiflen)
{
  unsigned int n = byte_count(modifs, modiflen, '\0') ;
  unsigned int vlen = envlen ;
  register unsigned int i = 0 ;
  if (envlen + n + 1 > vmax) return (errno = ENAMETOOLONG, 0) ;
  for (; i < envlen ; i++) v[i] = envp[i] ;
  for (i = 0 ; i < modiflen ; i += str_len(modifs + i) + 1)
  {
    unsigned int split = str_chr(modifs + i, '=') ;
    register unsigned int j = 0 ;
    for (; j < vlen ; j++)
      if (!byte_diff(modifs + i, split, v[j]) && (v[j][split] == '=')) break ;
    if (j < vlen) v[j] = v[--vlen] ;
    if (modifs[i + split]) v[vlen++] = modifs + i ;
  }
  v[vlen++] = 0 ;
  return vlen ;
}
