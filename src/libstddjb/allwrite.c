/* ISC license. */

#include <sys/types.h>
#include <skalibs/functypes.h>
#include <skalibs/allreadwrite.h>

size_t allwrite (int fd, char const *buf, size_t len)
{
  return allreadwrite((iofunc_t_ref)&fd_write, fd, (char *)buf, len) ;
}
