/* ISC license. */

#include <sys/mman.h>
#include <skalibs/cdb.h>

extern void cdb_free (struct cdb *c)
{
  if (c->map) munmap(c->map, c->size) ;
  *c = cdb_zero ;
}
