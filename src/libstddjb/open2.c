/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int open2 (char const *s, unsigned int flags)
{
  register int r ;
  do
    r = open(s, (int)flags) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
