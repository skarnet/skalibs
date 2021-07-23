/* ISC license. */

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <errno.h>

#include <skalibs/djbunix.h>
#include <skalibs/cdb.h>

int cdb_init (cdb *c, char const *file)
{
  char *map ;
  struct stat st ;
  int fd = openc_read(file) ;
  if (fd < 0) return 0 ;
  if (fstat(fd, &st) < 0) goto err ;
  if (st.st_size > UINT32_MAX) goto eoverf ;
  map = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0) ;
  if (map == MAP_FAILED) goto err ;
  c->map = map ;
  c->size = st.st_size ;
  fd_close(fd) ;
  return 1 ;

 eoverf:
  errno = EOVERFLOW ;
 err:
  fd_close(fd) ;
  return 0 ;
}
