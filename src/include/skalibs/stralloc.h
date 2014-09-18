/* ISC license. */

#ifndef STRALLOC_H
#define STRALLOC_H

#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>

typedef struct stralloc_s stralloc, *stralloc_ref ;
struct stralloc_s
{
  char *s ;
  unsigned int len ;
  unsigned int a ;
} ;

#define STRALLOC_ZERO { .s = 0, .len = 0, .a = 0 }
extern stralloc const stralloc_zero ;

extern int stralloc_ready_tuned (stralloc *, unsigned int, unsigned int, unsigned int, unsigned int) ;
#define stralloc_ready(sa, n) stralloc_ready_tuned(sa, (n), 8, 1, 8)
#define stralloc_readyplus(sa, n) stralloc_ready(sa, (sa)->len + (n))
extern void stralloc_free (stralloc *) ;
extern int stralloc_shrink (stralloc *) ;
extern int stralloc_copyb (stralloc *, char const *, unsigned int) ;
extern int stralloc_catb (stralloc *, char const *, unsigned int) ;
extern int stralloc_catv (stralloc *, siovec_t const *, unsigned int) ;
#define stralloc_copys(sa, s) stralloc_copyb(sa, (s), str_len(s))
#define stralloc_cats(sa, s) stralloc_catb(sa, (s), str_len(s))
#define stralloc_copy(sa1, sa2) stralloc_copyb(sa1, (sa2)->s, (sa2)->len)
#define stralloc_cat(sa1, sa2) stralloc_catb(sa1, (sa2)->s, (sa2)->len)
extern int stralloc_append (stralloc *, char) ;
extern void stralloc_reverse (stralloc *) ;
extern void stralloc_reverse_blocks (stralloc *, unsigned int) ;
#define stralloc_0(sa) stralloc_catb(sa, "", 1)
extern int stralloc_insertb (stralloc *, unsigned int, char const *, unsigned int) ;
#define stralloc_inserts(sa, offset, s) stralloc_insertb(sa, offset, (s), str_len(s))
#define stralloc_insert(sa1, offset, sa2) stralloc_insertb(sa1, offset, (sa2)->s, (sa2)->len)

#endif
