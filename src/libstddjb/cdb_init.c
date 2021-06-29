/* ISC license. */

#include <skalibs/bsdsnowflake.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <errno.h>

#include <skalibs/cdb.h>

int cdb_init (struct cdb *c, int fd)
{
  struct stat st ;
  char *map ;
  if (fstat(fd, &st) < 0) return -1 ;
  if (st.st_size > UINT32_MAX) return (errno = EOVERFLOW, -1) ;
  map = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, -1) ;
  if (map == MAP_FAILED) return -1 ;
  c->map = map ;
  c->size = st.st_size ;
  return 0 ;
}
