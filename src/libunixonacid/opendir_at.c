/* ISC license. */

/* Should not be necessary but old NetBSD/OpenBSD fail to
   properly expose fdopendir() otherwise */
#include <skalibs/nonposix.h>

#include <skalibs/direntry.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

DIR *opendir_at (int dfd, char const *name)
{
  DIR *dir ;
  int fd = openc_readatb(dfd, name) ;
  if (fd < 0) return 0 ;
  dir = fdopendir(fd) ;
  if (!dir) fd_close(fd) ;
  return dir ;
}
