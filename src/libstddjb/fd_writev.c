/* ISC license. */

#include <sys/uio.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>

ssize_t fd_writev (int fd, struct iovec const *v, unsigned int vlen)
{
  ssize_t r ;
  do r = writev(fd, v, vlen) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
