/* ISC license. */

#include <errno.h>
#include <skalibs/gensetdyn.h>
#include <skalibs/avlnode.h>
#include <skalibs/avltree.h>

int avltree_delete (avltree_ref t, void const *k)
{
  unsigned int r = avltree_root(t) ;
  unsigned int i = avlnode_delete(avltree_nodes(t), avltree_totalsize(t), &r, k, t->dtok, t->kcmp, t->external) ;
  if (i >= avltree_totalsize(t)) return (errno = ESRCH, 0) ;
  avltree_setroot(t, r) ;
  if (!gensetdyn_delete(&t->x, i)) return 0 ;
  return 1 ;
}
