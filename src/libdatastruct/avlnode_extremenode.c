/* ISC license. */

#include <skalibs/avlnode.h>

unsigned int avlnode_extremenode (avlnode const *s, unsigned int max, unsigned int r, int h)
{
  register unsigned int oldr = r ;
  for (; r < max ; oldr = r, r = s[r].child[h]) ;
  return oldr ;
}
