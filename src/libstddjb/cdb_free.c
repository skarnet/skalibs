/* ISC license. */

#include <sys/mman.h>
#include <errno.h>

#include <skalibs/cdb.h>

extern void cdb_free (struct cdb *c)
{
  if (c->map)
  {
    int e = errno ;
    munmap(c->map, c->size) ;
    errno = e ;
  }
  *c = cdb_zero ;
}
