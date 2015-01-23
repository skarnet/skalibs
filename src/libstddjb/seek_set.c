/* ISC license. */

#include <sys/types.h>
#include <unistd.h>
#include <skalibs/djbunix.h>

int seek_set (int fd, long pos)
{
  return lseek(fd, (off_t) pos, SEEK_SET) ;
}
