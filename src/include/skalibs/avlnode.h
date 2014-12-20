/* ISC license. */

#ifndef AVLNODE_H
#define AVLNODE_H

#include <skalibs/gccattributes.h>
#include <skalibs/functypes.h>


#define AVLNODE_MAXDEPTH 49  /* enough for 2^32 nodes in the worst case */

typedef int avliterfunc_t (unsigned int, unsigned int, void *) ;
typedef avliterfunc_t *avliterfunc_t_ref ;

typedef struct avlnode_s avlnode, *avlnode_ref ;
struct avlnode_s
{
  unsigned int data ;
  unsigned int child[2] ;
  signed char balance : 2 ;
} ;

#define AVLNODE_ZERO { .data = 0, .child = { (unsigned int)-1, (unsigned int)-1 }, .balance = 0 }
extern avlnode const avlnode_zero ;

extern unsigned int avlnode_searchnode (avlnode const *, unsigned int, unsigned int, void const *, dtokfunc_t_ref, cmpfunc_t_ref, void *) ;
extern int avlnode_search (avlnode const *, unsigned int, unsigned int, void const *, unsigned int *, dtokfunc_t_ref, cmpfunc_t_ref, void *) ;
extern unsigned int avlnode_height (avlnode const *, unsigned int, unsigned int) gccattr_pure ;

extern unsigned int avlnode_extremenode (avlnode const *, unsigned int, unsigned int, int) gccattr_pure ;
#define avlnode_minnode(s, max, r) avlnode_extremenode(s, max, (r), 0)
#define avlnode_maxnode(s, max, r) avlnode_extremenode(s, max, (r), 1)

extern int avlnode_extreme (avlnode const *, unsigned int, unsigned int, int, unsigned int *) ;
#define avlnode_min(s, max, r, data) avlnode_extreme(s, max, (r), 0, data)
#define avlnode_max(s, max, r, data) avlnode_extreme(s, max, (r), 1, data)

extern unsigned int avlnode_insertnode (avlnode *, unsigned int, unsigned int, unsigned int, dtokfunc_t_ref, cmpfunc_t_ref, void *) ;
extern unsigned int avlnode_delete (avlnode *, unsigned int, unsigned int *, void const *, dtokfunc_t_ref, cmpfunc_t_ref, void *) ;
#define avlnode_deletenode(s, max, r, i, dtok, f, p) avlnode_delete(s, max, r, (*(dtok))((s)[i].data), dtok, f, p)

extern int avlnode_iter (avlnode *, unsigned int, unsigned int, avliterfunc_t_ref, void *) ;

#endif
