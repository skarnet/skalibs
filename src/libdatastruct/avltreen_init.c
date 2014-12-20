/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/genset.h>
#include <skalibs/avlnode.h>
#include <skalibs/avltreen.h>

void avltreen_init (avltreen *t, avlnode_ref storage, unsigned int *freelist, unsigned int size, dtokfunc_t_ref dtok, cmpfunc_t_ref f, void *p)
{
  GENSET_init(&t->x, avlnode, storage, freelist, size) ;
  t->root = size ;
  t->dtok = dtok ;
  t->kcmp = f ;
  t->external = p ;
}
