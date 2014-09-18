/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int open3 (char const *s, unsigned int flags, unsigned int mode)
{
  register int r ;
  do
    r = open(s, (int)flags, (mode_t)mode) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
