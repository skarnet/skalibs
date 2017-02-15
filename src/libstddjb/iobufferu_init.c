/* ISC license. */

#include <skalibs/alloc.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>
#include <skalibs/iobuffer.h>

int iobufferu_init (iobufferu *b, int fdin, int fdout)
{
  register char *x = alloc(IOBUFFERU_SIZE) ;
  if (!x) return 0 ;
  b->buf = x ;
  buffer_init(&b->b[0], &fd_readv, fdin, x, IOBUFFERU_SIZE) ;
  buffer_init(&b->b[1], &fd_writev, fdout, x, IOBUFFERU_SIZE) ;
  return 1 ;
}
