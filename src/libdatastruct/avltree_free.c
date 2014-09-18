/* ISC license. */

#include <skalibs/gensetdyn.h>
#include <skalibs/avltree.h>

void avltree_free (avltree_ref t)
{
  gensetdyn_free(&t->x) ;
  *t = avltree_zero ;
}
