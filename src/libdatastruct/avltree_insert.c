/* ISC license. */

#include <skalibs/avltree.h>

int avltree_insert (avltree_ref t, unsigned int d)
{
  unsigned int i ;
  if (!avltree_newnode(t, d, &i)) return 0 ;
  avltree_insertnode(t, i) ;
  return 1 ;
}
