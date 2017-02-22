/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int open3 (char const *s, unsigned int flags, unsigned int mode)
{
  int r ;
  do r = open(s, flags, mode) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
