/* ISC license. */

#ifndef AVLTREE_H
#define AVLTREE_H

#include <skalibs/functypes.h>
#include <skalibs/gensetdyn.h>
#include <skalibs/avlnode.h>

typedef struct avltree_s avltree, *avltree_ref ;
struct avltree_s
{
  gensetdyn x ;
  unsigned int root ;
  dtokfunc_t_ref dtok ;
  cmpfunc_t_ref kcmp ;
  void *external ;
} ;

#define AVLTREE_ZERO { .x = GENSETDYN_ZERO, .root = (unsigned int)-1, .dtok = 0, .kcmp = 0, .external = 0 }
extern avltree const avltree_zero ;
#define avltree_len(t) gensetdyn_n(&(t)->x)
#define avltree_totalsize(t) ((t)->x.storage.len)
#define avltree_nodes(t) ((avlnode_ref)(t)->x.storage.s)
#define avltree_data(t, i) (avltree_nodes(t)[i].data)
#define avltree_root(t) ((t)->root)
#define avltree_setroot(t, r) ((t)->root = (r))

extern void avltree_free (avltree_ref) ;
extern void avltree_init (avltree_ref, unsigned int, unsigned int, unsigned int, dtokfunc_t_ref, cmpfunc_t_ref, void *) ;
#define AVLTREE_INIT(b, num, den, dtk, f, p) { .x = GENSETDYN_INIT(avlnode, (b), num, den), .root = (unsigned int)-1, .dtok = (dtk), .kcmp = (f), .external = (p) }

#define avltree_searchnode(t, k) avlnode_searchnode(avltree_nodes(t), avltree_totalsize(t), avltree_root(t), k, (t)->dtok, (t)->kcmp, (t)->external)
#define avltree_search(t, k, data) avlnode_search(avltree_nodes(t), avltree_totalsize(t), avltree_root(t), k, (data), (t)->dtok,  (t)->kcmp, (t)->external)

#define avltree_height(t) avlnode_height(avltree_nodes(t), avltree_totalsize(t), avltree_root(t))

#define avltree_extremenode(t, h) avlnode_extremenode(avltree_nodes(t), avltree_totalsize(t), avltree_root(t), h)
#define avltree_minnode(t) avltree_extremenode((t), 0)
#define avltree_maxnode(t) avltree_extremenode((t), 1)

#define avltree_extreme(t, h, data) avlnode_extreme(avltree_nodes(t), avltree_totalsize(t), avltree_root(t), (h), data)
#define avltree_min(t, data) avltree_extreme((t), 0, data)
#define avltree_max(t, data) avltree_extreme((t), 1, data)

extern int avltree_newnode (avltree_ref, unsigned int, unsigned int *) ;
#define avltree_insertnode(t, i) avltree_setroot(t, avlnode_insertnode(avltree_nodes(t), avltree_totalsize(t), avltree_root(t), i, (t)->dtok, (t)->kcmp, (t)->external))
extern int avltree_insert (avltree_ref, unsigned int) ;

#define avltree_deletenode(t, i) avltree_delete(t, (*(t)->dtok)(avltree_data(t, i)))
extern int avltree_delete (avltree_ref, void const *) ;

#define avltree_iter(t, f, p) avlnode_iter(avltree_nodes(t), avltree_totalsize(t), avltree_root(t), f, p)

#endif
