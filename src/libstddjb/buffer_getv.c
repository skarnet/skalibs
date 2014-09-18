/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/diuint.h>
#include <skalibs/siovec.h>

int buffer_getv (buffer *b, siovec_t const *v, unsigned int n)
{
  diuint w = DIUINT_ZERO ;
  register int r = buffer_getvall(b, v, n, &w) ;
  return r == -1 ? errno == EPIPE ? (errno = 0, 0) : -1 :
         !r ? (errno = EWOULDBLOCK, -1) :
         (int)(siovec_len(v, w.left) + w.right) ;
}
