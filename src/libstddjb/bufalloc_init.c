/* ISC license. */

#include <skalibs/bufalloc.h>

void bufalloc_init (bufalloc *ba, ssize_t (*op)(int, char const *, size_t), int fd)
{
  ba->x.len = 0 ;
  ba->op = op ;
  ba->fd = fd ;
  ba->p = 0 ;
}
