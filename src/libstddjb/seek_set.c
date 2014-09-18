/* ISC license. */

#include <sys/types.h>
#include <unistd.h>
#include <skalibs/djbunix.h>

#define SET 0 /* sigh */

int seek_set (int fd, long pos)
{
  if (lseek(fd, (off_t) pos, SET) == -1) return -1 ;
  return 0 ;
}
