/* ISC license. */

#include <stdint.h>
#include <skalibs/cdb.h>

uint32_t cdb_hashadd (uint32_t h, unsigned char c)
{
  h += (h << 5) ;
  return h ^ c ;
}

uint32_t cdb_hash (char const *buf, unsigned int len)
{
  uint32_t h = CDB_HASHSTART ;
  while (len--) h = cdb_hashadd(h, *buf++) ;
  return h ;
}
