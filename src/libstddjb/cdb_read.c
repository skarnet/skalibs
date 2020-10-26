/* ISC license. */

#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <skalibs/allreadwrite.h>
#include <skalibs/cdb.h>
#include <skalibs/posixishard.h>

int cdb_read (struct cdb *c, char *buf, unsigned int len, uint32_t pos)
{
  if (c->map)
  {
    if ((pos > c->size) || (c->size - pos < len)) return (errno = EPROTO, -1) ;
    memcpy(buf, c->map + pos, len) ;
  }
  else
  {
    if (lseek(c->fd, pos, SEEK_SET) < 0) return -1 ;
    if (allread(c->fd, buf, len) < len) return -1 ;
  }
  return 0 ;
}
