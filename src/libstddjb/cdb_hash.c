/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/cdb.h>

uint32 cdb_hashadd (uint32 h, unsigned char c)
{
  h += (h << 5) ;
  return h ^ c ;
}

uint32 cdb_hash (char const *buf, unsigned int len)
{
  uint32 h = CDB_HASHSTART ;
  while (len--) h = cdb_hashadd(h, *buf++) ;
  return h ;
}
