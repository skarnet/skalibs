/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/genalloc.h>
#include <skalibs/envalloc.h>

int envalloc_uniq (genalloc *v, char delim)
{
  unsigned int m = 0 ;
  register unsigned int i = 0 ;
  for (; i < genalloc_len(char const *, v) ; i++)
  {
    register unsigned int j = i+1 ;
    char const *s = genalloc_s(char const *, v)[i] ;
    unsigned int n = str_chr(s, delim) ;
    if (delim && !s[n]) return (errno = EINVAL, -1) ;
    for (; j < genalloc_len(char const *, v) ; j++)
    {
      register char const **p = genalloc_s(char const *, v) ;
      if (!str_diffn(s, p[j], n))
      {
        register unsigned int len = genalloc_len(char const *, v) - 1 ;
        genalloc_setlen(char const *, v, len) ;
        p[j] = p[len] ;
        m++ ;
      }
    }
  }
  return (int)m ;
}
