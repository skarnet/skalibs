/* ISC license. */

#include <stdint.h>
#include <skalibs/cdb.h>

int cdb_successor (struct cdb *c, char const *key, unsigned int klen)
{
  uint32_t kpos ;
  if (key)
  {
    int r = cdb_find(c, key, klen) ;
    if (r < 1) return r ;
    kpos = c->dpos + c->dlen ;
  }
  else cdb_traverse_init(c, &kpos) ;
  return cdb_nextkey(c, &kpos) ;
}
