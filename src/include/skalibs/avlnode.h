/* ISC license. */

#ifndef AVLNODE_H
#define AVLNODE_H

#include <stdint.h>
#include <skalibs/gccattributes.h>
#include <skalibs/functypes.h>


#define AVLNODE_MAXDEPTH 49  /* enough for 2^32 nodes in the worst case */

typedef int avliterfunc_t (uint32_t, unsigned int, void *) ;
typedef avliterfunc_t *avliterfunc_t_ref ;

typedef struct avlnode_s avlnode, *avlnode_ref ;
struct avlnode_s
{
  uint32_t data ;
  uint32_t child[2] ;
  signed char balance : 2 ;
} ;

#define AVLNODE_ZERO { .data = 0, .child = { UINT32_MAX, UINT32_MAX }, .balance = 0 }
extern avlnode const avlnode_zero ;

extern uint32_t avlnode_searchnode (avlnode const *, uint32_t, uint32_t, void const *, dtokfunc_t_ref, cmpfunc_t_ref, void *) ;
extern int avlnode_search (avlnode const *, uint32_t, uint32_t, void const *, uint32_t *, dtokfunc_t_ref, cmpfunc_t_ref, void *) ;
extern unsigned int avlnode_height (avlnode const *, uint32_t, uint32_t) gccattr_pure ;

extern uint32_t avlnode_extremenode (avlnode const *, uint32_t, uint32_t, int) gccattr_pure ;
#define avlnode_minnode(s, max, r) avlnode_extremenode(s, max, (r), 0)
#define avlnode_maxnode(s, max, r) avlnode_extremenode(s, max, (r), 1)

extern int avlnode_extreme (avlnode const *, uint32_t, uint32_t, int, uint32_t *) ;
#define avlnode_min(s, max, r, data) avlnode_extreme(s, max, (r), 0, data)
#define avlnode_max(s, max, r, data) avlnode_extreme(s, max, (r), 1, data)

extern uint32_t avlnode_insertnode (avlnode *, uint32_t, uint32_t, uint32_t, dtokfunc_t_ref, cmpfunc_t_ref, void *) ;
extern uint32_t avlnode_delete (avlnode *, uint32_t, uint32_t *, void const *, dtokfunc_t_ref, cmpfunc_t_ref, void *) ;
#define avlnode_deletenode(s, max, r, i, dtok, f, p) avlnode_delete(s, max, r, (*(dtok))((s)[i].data), dtok, f, p)

extern uint32_t avlnode_iter_nocancel (avlnode *, uint32_t, uint32_t, uint32_t, avliterfunc_t_ref, void *) ;
#define avlnode_iter(tree, max, root, f, stuff) (avlnode_iter_nocancel(tree, max, max, root, f, stuff) == (max))
extern int avlnode_iter_withcancel (avlnode *, uint32_t, uint32_t, avliterfunc_t_ref, avliterfunc_t_ref, void *) ;

#endif
