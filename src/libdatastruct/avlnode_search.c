/* ISC license. */

#include <errno.h>
#include <skalibs/avlnode.h>

int avlnode_search (avlnode const *s, unsigned int max, unsigned int r, void const *k, unsigned int *data, dtokfunc_t_ref dtok, cmpfunc_t_ref f, void *p)
{
  register unsigned int i = avlnode_searchnode(s, max, r, k, dtok, f, p) ;
  if (i >= max) return (errno = ESRCH, 0) ;
  *data = s[i].data ;
  return 1 ;
}
