/* ISC license. */

#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/bytestr.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/uint32.h>
#include <skalibs/djbunix.h>
#include <skalibs/cdb.h>

int cdb_read (struct cdb *c, char *buf, unsigned int len, uint32 pos)
{
  if (c->map)
  {
    if ((pos > c->size) || (c->size - pos < len)) return (errno = EPROTO, -1) ;
    byte_copy(buf, len, c->map + pos) ;
  }
  else
  {
    if (seek_set(c->fd, pos) < 0) return -1 ;
    if (allread(c->fd, buf, len) < len) return -1 ;
  }
  return 0 ;
}
