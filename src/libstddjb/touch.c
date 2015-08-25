/* ISC license. */

#include <skalibs/djbunix.h>

int touch (char const *file)
{
  register int fd = open_create(file) ;
  if (fd < 0) return 0 ;
  fd_close(fd) ;
  return 1 ;
}
