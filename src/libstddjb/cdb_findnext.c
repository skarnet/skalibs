/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/uint32.h>
#include <skalibs/cdb.h>

static int match (struct cdb *c, char const *key, unsigned int len, uint32 pos)
{
  char buf[1024] ;
  while (len > 0)
  {
    register unsigned int n = 1024 ;
    if (n > len) n = len ;
    if (cdb_read(c, buf, n, pos) < 0) return -1 ;
    if (byte_diff(buf, n, key)) return 0 ;
    pos += n ; key += n ; len -= n ;
  }
  return 1 ;
}

int cdb_findnext (struct cdb *c, char const *key, unsigned int len)
{
  char buf[8] ;
  uint32 pos ;
  uint32 u ;

  if (!c->loop)
  {
    u = cdb_hash(key, len) ;
    if (cdb_read(c, buf, 8, (u << 3) & 2047) < 0) return -1 ;
    uint32_unpack(buf + 4, &c->hslots) ;
    if (!c->hslots) return 0 ;
    uint32_unpack(buf, &c->hpos) ;
    c->khash = u ;
    u >>= 8 ;
    u %= c->hslots ;
    u <<= 3 ;
    c->kpos = c->hpos + u ;
  }

  while (c->loop < c->hslots)
  {
    if (cdb_read(c, buf, 8, c->kpos) < 0) return -1 ;
    uint32_unpack(buf + 4, &pos) ;
    if (!pos) return 0 ;
    c->loop++ ;
    c->kpos += 8 ;
    if (c->kpos == c->hpos + (c->hslots << 3)) c->kpos = c->hpos ;
    uint32_unpack(buf, &u) ;
    if (u == c->khash)
    {
      if (cdb_read(c, buf, 8, pos) < 0) return -1 ;
      uint32_unpack(buf, &u) ;
      if (u == len)
	  switch (match(c, key, len, pos + 8))
      {
        case -1:
          return -1 ;
        case 1:
          uint32_unpack(buf + 4, &c->dlen) ;
          c->dpos = pos + 8 + len ;
          return 1 ;
      }
    }
  }
  return 0 ;
}
