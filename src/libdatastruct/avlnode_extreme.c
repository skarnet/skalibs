/* ISC license. */

#include <errno.h>
#include <skalibs/avlnode.h>

int avlnode_extreme (avlnode const *s, unsigned int max, unsigned int r, int h, unsigned int *k)
{
  register unsigned int i = avlnode_extremenode(s, max, r, h) ;
  if (i >= max) return (errno = ESRCH, 0) ;
  *k = s[i].data ;
  return 1 ;
}
