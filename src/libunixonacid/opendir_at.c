/* ISC license. */

#include <skalibs/direntry.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

DIR *opendir_at (int dfd, char const *name)
{
  DIR *dir ;
  int fd = open_readatb(dfd, name) ;
  if (fd < 0) return 0 ;
  dir = fdopendir(fd) ;
  if (!dir) fd_close(fd) ;
  return dir ;
}
