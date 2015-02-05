/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/bufalloc.h>

void bufalloc_init (bufalloc *ba, int (*op)(int, char const *, unsigned int), int fd)
{
  ba->x = stralloc_zero ;
  ba->op = op ;
  ba->fd = fd ;
  ba->p = 0 ;
}
