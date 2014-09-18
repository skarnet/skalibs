/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/error.h>

int sanitize_read (int r)
{
  return r == -1 ? error_isagain(errno) ? (errno = 0, 0) : -1 :
         !r ? (errno = EPIPE, -1) : r ;
}
