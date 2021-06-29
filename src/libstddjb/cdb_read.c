/* ISC license. */

#include <string.h>
#include <errno.h>

#include <skalibs/cdb.h>
#include <skalibs/posixishard.h>

int cdb_read (struct cdb *c, char *buf, unsigned int len, uint32_t pos)
{
  if ((pos > c->size) || (c->size - pos < len)) return (errno = EPROTO, -1) ;
  memcpy(buf, c->map + pos, len) ;
  return 0 ;
}
