/* ISC license. */

#include <skalibs/avlnode.h>
#include "avlnode-internal.h"

unsigned int avlnode_rotate (avlnode *s, unsigned int max, unsigned int i, int h)
{
  register unsigned int j = s[i].child[!h] ;
  s[i].child[!h] = s[j].child[h] ;
  s[j].child[h] = i ;
  if (s[j].balance * avlnode_sfromu(h) < 0) s[i].balance = s[j].balance = 0 ;
  else s[j].balance = avlnode_sfromu(h) ;
  (void)max ;
  return j ;
}
