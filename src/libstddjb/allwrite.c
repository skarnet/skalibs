/* ISC license. */

#include <skalibs/allreadwrite.h>

unsigned int allwrite (int fd, char const *buf, unsigned int len)
{
  return allreadwrite((iofunc_t_ref)&fd_write, fd, (char *)buf, len) ;
}
