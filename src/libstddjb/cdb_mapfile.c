/* ISC license. */

#include <errno.h>
#include <skalibs/djbunix.h>
#include <skalibs/cdb.h>

int cdb_mapfile (struct cdb *c, char const *file)
{
  int fd = open_readb(file) ;
  if (fd < 0) return 0 ;
  if (!cdb_init_map(c, fd, 1))
  {
    int e = errno ;
    fd_close(fd) ;
    errno = e ;
    return 0 ;
  }
  fd_close(fd) ;
  return 1 ;
}
