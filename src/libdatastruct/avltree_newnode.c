/* ISC license. */

#include <errno.h>
#include <skalibs/gensetdyn.h>
#include <skalibs/avlnode.h>
#include <skalibs/avltree.h>

int avltree_newnode (avltree *t, unsigned int data, unsigned int *i)
{
  if (!gensetdyn_new(&t->x, i)) return 0 ;
  {
    register avlnode *s = avltree_nodes(t) ;
    s[*i].data = data ;
    s[*i].child[0] = s[*i].child[1] = (unsigned int)-1 ;
    s[*i].balance = 0 ;
  }
  return 1 ;
}
