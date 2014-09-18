/* ISC license. */

#include <skalibs/avlnode.h>
#include "avlnode-internal.h"

unsigned int avlnode_doublerotate (avlnode_ref s, unsigned int max, unsigned int i, int h)
{
  register unsigned int j = s[i].child[!h] ;
  register unsigned int k = s[j].child[h] ;
  s[i].child[!h] = s[k].child[h] ;
  s[j].child[h] = s[k].child[!h] ;
  s[k].child[!h] = j ;
  s[k].child[h] = i ;
  s[h ? i : j].balance = (s[k].balance < 0) ;
  s[h ? j : i].balance = -(s[k].balance > 0) ;
  s[k].balance = 0 ;
  (void)max ;
  return k ;
}
