/* ISC license. */

#ifndef GENSET_H
#define GENSET_H

#include <skalibs/functypes.h>

typedef struct genset_s genset, *genset_ref ;
struct genset_s
{
  char *storage ;
  unsigned int *freelist ;
  unsigned int esize ;
  unsigned int max ;
  unsigned int sp ;
} ;

#define GENSET_ZERO { .storage = 0, .freelist = 0, .esize = 1, .max = 0, .sp = 0 }
extern void genset_init (genset *, void *, unsigned int *, unsigned int, unsigned int) ;
#define GENSET_init(g, type, storage, fl, size) genset_init(g, storage, fl, sizeof(type), size)

#define genset_p(type, g, i) ((type *)((g)->storage + (i) * (g)->esize))
extern unsigned int genset_new (genset *) ;
extern int genset_delete (genset *, unsigned int) ;
#define genset_n(g) ((g)->max - (g)->sp)
extern unsigned int genset_iter_nocancel (genset *, unsigned int, iterfunc_t_ref, void *) ;
#define genset_iter(g, f, stuff) genset_iter_nocancel(g, (g)->max, f, stuff)
extern int genset_iter_withcancel (genset *, iterfunc_t_ref, iterfunc_t_ref, void *) ;

#define GENSETB_TYPE(type, size) struct { type storage[size] ; unsigned int freelist[size] ; genset info ; }
#define GENSETB_init(type, g, size) GENSET_init(&(g)->info, type, (g)->storage, (g)->freelist, size)
#define gensetb_p(type, g, i) genset_p(type, &(g)->info, i)
#define gensetb_new(g) genset_new(&(g)->info)
#define gensetb_delete(g, i) genset_delete(&(g)->info, i)
#define gensetb_n(g) genset_n(&(g)->info)
#define gensetb_iter(g, f, p) genset_iter(&(g)->info, f, p)

#endif
