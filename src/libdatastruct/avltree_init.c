/* ISC license. */

#include <errno.h>
#include <skalibs/functypes.h>
#include <skalibs/gensetdyn.h>
#include <skalibs/avlnode.h>
#include <skalibs/avltree.h>

void avltree_init (avltree *t, unsigned int base, unsigned int fracnum, unsigned int fracden, dtokfunc_t_ref dtok, cmpfunc_t_ref f, void *p)
{
  gensetdyn_init(&t->x, sizeof(avlnode), base, fracnum, fracden) ;
  t->root = (unsigned int)-1 ;
  t->dtok = dtok ;
  t->kcmp = f ;
  t->external = p ;
}
