/* ISC license. */

#include <skalibs/alloc.h>
#include <skalibs/buffer.h>
#include <skalibs/iobuffer.h>

int iobufferu_init (iobufferu_ref b, int fdin, int fdout)
{
  register char *x = alloc(IOBUFFERU_SIZE) ;
  if (!x) return 0 ;
  b->buf = x ;
  buffer_init(&b->b[0], &buffer_read, fdin, x, IOBUFFERU_SIZE) ;
  buffer_init(&b->b[1], &buffer_write, fdout, x, IOBUFFERU_SIZE) ;
  return 1 ;
}
