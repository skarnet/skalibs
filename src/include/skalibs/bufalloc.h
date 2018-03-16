/* ISC license. */

#ifndef BUFALLOC_H
#define BUFALLOC_H

#include <sys/types.h>
#include <skalibs/gccattributes.h>
#include <skalibs/stralloc.h>

typedef struct bufalloc bufalloc, *bufalloc_ref ;
struct bufalloc
{
  stralloc x ;
  size_t p ;
  int fd ;
  ssize_t (*op) (int, char const *, size_t) ;
} ;

#define BUFALLOC_ZERO { STRALLOC_ZERO, 0, -1, 0 }
#define BUFALLOC_INIT(f, d) { STRALLOC_ZERO, 0, (d), (f) }
extern void bufalloc_init (bufalloc *, ssize_t (*)(int, char const *, size_t), int) ;
#define bufalloc_shrink(ba) stralloc_shrink(&(ba)->x)
#define bufalloc_free(ba) stralloc_free(&(ba)->x)
#define bufalloc_put(ba, s, n) stralloc_catb(&(ba)->x, s, n)
#define bufalloc_puts(ba, s) stralloc_cats(&(ba)->x, s)
#define bufalloc_putv(ba, v, n) stralloc_catv(&(ba)->x, v, n)
#define bufalloc_unput(ba, n) ((ba)->x.len -= (n))
#define bufalloc_fd(ba) ((ba)->fd)
extern int bufalloc_getfd (bufalloc const *) gccattr_pure ;
extern int bufalloc_flush (bufalloc *) ;
extern void bufalloc_clean (bufalloc *) ;
#define bufalloc_len(ba) ((ba)->x.len - (ba)->p)
extern size_t bufalloc_getlen (bufalloc const *) gccattr_pure ;
#define bufalloc_isempty(ba) ((ba)->x.len == (ba)->p)

extern bufalloc bufalloc_1_ ;
#define bufalloc_1 (&bufalloc_1_)
extern bufalloc bufalloc_2_ ;
#define bufalloc_2 (&bufalloc_2_)

#endif
