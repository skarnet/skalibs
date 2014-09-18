/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/avlnode.h>
#include "avlnode-internal.h"

unsigned int avlnode_searchnode (avlnode const *s, unsigned int max, unsigned int r, void const *k, dtokfunc_t_ref dtok, cmpfunc_t_ref f, void *p)
{
  while (r < max)
  {
    register int h = (*f)(k, (*dtok)(s[r].data, p), p) ;
    if (!h) break ;
    r = s[r].child[avlnode_ufroms(h)] ;
  }
  return r ;
}
