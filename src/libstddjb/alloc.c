/* ISC license. */

#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <skalibs/sysdeps.h>
#include <skalibs/alloc.h>
#include "alloc-internal.h"

#ifdef DEBUG_ALLOC
# include "buffer.h"
# include "strerr2.h"
# include "lolstdio.h"
# define PLM(...) (bprintf(buffer_2, "%s: debug_alloc: ", PROG), bprintf(buffer_2, __VA_ARGS__), buffer_putflush(buffer_2, "\n", 1))
#endif

aligned_char *alloc (size_t n)
{
  register aligned_char *p = n ? (aligned_char *)malloc(n) : (aligned_char *)alloc_0 ;
#ifdef DEBUG_ALLOC
  static unsigned int counter = 0 ;
  PLM("alloc(%u): %p. Allocated: %u", n, p, ++counter) ;
#endif
  return p ;
}

void alloc_free (void *p)
{
  register int e = errno ;
#ifdef DEBUG_ALLOC
  static unsigned int counter = 0 ;
  PLM("alloc_free(%p). Freed: %u", p, ++counter) ;
#endif
#ifndef SKALIBS_HASMALLOC0
  if (p != alloc_0)
#endif
  free(p) ;
  errno = e ;
}

int alloc_realloc (aligned_char **x, size_t n)
{
  aligned_char *y = n ? (aligned_char *)realloc(*x, n) : (free(*x), alloc_0) ;
#ifdef DEBUG_ALLOC
  PLM("alloc_realloc(&%p) -> new address = %p", *x, y) ;
#endif
  if (!y) return 0 ;
  *x = y ;
  return 1 ;
}
