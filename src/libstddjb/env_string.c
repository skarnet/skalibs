/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/env.h>

int env_string (stralloc *sa, char const *const *envp, unsigned int envlen)
{
  unsigned int salen = sa->len ;
  register unsigned int i = 0 ;
  for (; i < envlen ; i++)
  {
    if (!stralloc_cats(sa, envp[i]) || !stralloc_0(sa))
    {
      sa->len = salen ;
      return 0 ;
    }
  }
  return 1 ;
}
