/* ISC license. */

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <errno.h>
#include <skalibs/cdb.h>

int cdb_init_map (struct cdb *c, int fd, int domap)
{
  if (domap)
  {
    struct stat st ;
    char *map ;
    if (fstat(fd, &st) < 0) return 0 ;
    if (st.st_size > UINT32_MAX) return (errno = EOVERFLOW, 0) ;
    map = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0) ;
    if (map == MAP_FAILED) return 0 ;
    c->fd = -fd-2 ;
    c->map = map ;
    c->size = st.st_size ;
  }
  else c->fd = fd ;
  return 1 ;
}
