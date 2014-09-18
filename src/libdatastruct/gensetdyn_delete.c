/* ISC license. */

#include <errno.h>
#include <skalibs/genalloc.h>
#include <skalibs/gensetdyn.h>

int gensetdyn_delete (gensetdyn_ref g, unsigned int i)
{
  return (i >= g->storage.len) ? (errno = EINVAL, 0) :
    genalloc_catb(unsigned int, &g->freelist, &i, 1) ;
}
