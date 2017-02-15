/* ISC license. */

#include <sys/types.h>
#include <skalibs/stralloc.h>
#include <skalibs/bufalloc.h>

void bufalloc_init (bufalloc *ba, int (*op)(int, char const *, size_t), int fd)
{
  ba->x = stralloc_zero ;
  ba->op = op ;
  ba->fd = fd ;
  ba->p = 0 ;
}
