/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/cdb.h>

int cdb_mapfile (struct cdb *c, char const *file)
{
  int fd = openc_read(file) ;
  if (fd < 0) return 0 ;
  if (cdb_init(c, fd) == -1)
  {
    fd_close(fd) ;
    return 0 ;
  }
  fd_close(fd) ;
  return 1 ;
}
