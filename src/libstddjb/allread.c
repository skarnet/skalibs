/* ISC license. */

#include <sys/types.h>
#include <skalibs/allreadwrite.h>

size_t allread (int fd, char *buf, size_t len)
{
  return allreadwrite(&fd_readv, fd, buf, len) ;
}
