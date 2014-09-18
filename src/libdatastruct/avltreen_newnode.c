/* ISC license. */

#include <skalibs/genset.h>
#include <skalibs/avlnode.h>
#include <skalibs/avltreen.h>

unsigned int avltreen_newnode (avltreen_ref t, unsigned int d)
{
  register unsigned int i = genset_new(&t->x) ;
  if (i < avltreen_totalsize(t))
  {
    register avlnode_ref s = avltreen_nodes(t) ;
    s[i].data = d ;
    s[i].child[0] = s[i].child[1] = avltreen_totalsize(t) ;
    s[i].balance = 0 ;
  }
  return i ;
}
