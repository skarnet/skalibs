/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/error.h>

int unsanitize_read (int r)
{
  return r == -1 ? errno == EPIPE ? (errno = 0, 0) : -1 :
         !r ? (errno = EWOULDBLOCK, -1) : r ;
}
