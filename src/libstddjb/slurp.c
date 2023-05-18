/* ISC license. */

#include <skalibs/djbunix.h>

int slurp (stralloc *sa, int fd)
{
  return slurpn(fd, sa, 0) ;
}
