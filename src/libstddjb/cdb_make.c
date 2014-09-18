/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <skalibs/uint32.h>
#include <skalibs/diuint32.h>
#include <skalibs/genalloc.h>
#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <skalibs/cdb.h>
#include <skalibs/cdb_make.h>

static void cdb_make_free (struct cdb_make *c)
{
  struct cdb_make zero = CDB_MAKE_ZERO ;
  genalloc_free(diuint32, &c->hplist) ;
  *c = zero ;
}

int cdb_make_start (struct cdb_make *c, int fd)
{
  c->hplist = genalloc_zero ;
  c->fd = fd ;
  c->pos = 2048 ;
  buffer_init(&c->b, &buffer_write, fd, c->buf, BUFFER_OUTSIZE) ;
  return seek_set(fd, c->pos) ;
}

static int posplus (struct cdb_make *c, uint32 len)
{
  register uint32 newpos = c->pos + len ;
  if (newpos < len) return (errno = ENOMEM, 0) ;
  c->pos = newpos ;
  return 1 ;
}

static int cdb_make_addend (struct cdb_make *c, unsigned int keylen, unsigned int datalen, uint32 h)
{
  diuint32 blah = { h, c->pos } ;
  if (!genalloc_append(diuint32, &c->hplist, &blah) || !posplus(c, 8) || !posplus(c, keylen) || !posplus(c, datalen))
  {
    cdb_make_free(c) ;
    return -1 ;
  }
  return 0 ;
}

static int cdb_make_addbegin (struct cdb_make *c, unsigned int keylen, unsigned int datalen)
{
  char buf[8] ;
  if ((keylen > 0xffffffff) || (datalen > 0xffffffff))
  {
    errno = ENOMEM ;
    goto err ;
  }
  uint32_pack(buf, keylen) ;
  uint32_pack(buf + 4, datalen) ;
  if (buffer_put(&c->b, buf, 8) < 0) goto err ;
  return 0 ;
err:
  cdb_make_free(c) ;
  return -1 ;
}

int cdb_make_add (struct cdb_make *c, char const *key, unsigned int keylen, char const *data, unsigned int datalen)
{
  if ((cdb_make_addbegin(c, keylen, datalen) < 0)
   || (buffer_put(&c->b, key, keylen) < 0)
   || (buffer_put(&c->b, data, datalen) < 0)
   || (cdb_make_addend(c, keylen, datalen, cdb_hash(key, keylen)) < 0))
    return -1 ;
  return 0 ;
}

int cdb_make_finish (struct cdb_make *c)
{
  uint32 count[256] ;
  uint32 start[256] ;
  char final[2048] ;
  unsigned int size = 1 ;
  unsigned int n = genalloc_len(diuint32, &c->hplist) ;
  register unsigned int i = 0 ;
  register diuint32 *hp = genalloc_s(diuint32, &c->hplist) ;

  for ( ; i < 256 ; i++) count[i] = 0 ;
  for (i = 0 ; i < n ; i++) ++count[hp[i].left & 255] ;

  {
    register uint32 u = 0 ;
    for (i = 0 ; i < 256 ; i++) start[i] = u += count[i] ; /* bounded by n */
    for (i = 0 ; i < 256 ; i++)
    {
      u = count[i] << 1 ;
      if (u > size) size = u ;
    }
    size += n ; /* no overflow possible up to now */
    u = 0xffffffffUL ; u /= sizeof(diuint32) ;
    if (size > u) return (errno = ENOMEM, -1) ;
  }
  i = n ;
  {
    diuint32 split[size] ;
    while (i--) split[--start[hp[i].left & 255]] = hp[i] ;
    genalloc_free(diuint32, &c->hplist) ;
    hp = split + n ;

    for (i = 0 ; i < 256 ; ++i)
    {
      char buf[8] ;
      register uint32 k = count[i] ;
      register uint32 len = k << 1 ; /* no overflow possible */
      register diuint32 *p = split + start[i] ;
      register unsigned int j = 0 ;

      uint32_pack(final + (i << 3), c->pos) ;
      uint32_pack(final + (i << 3) + 4, len) ;

      for ( ; j < len ; j++) hp[j].left = hp[j].right = 0 ;
      for (j = 0 ; j < k ; j++)
      {
        register uint32 where = (p->left >> 8) % len ;
        while (hp[where].right) if (++where == len) where = 0 ;
        hp[where] = *p++ ;
      }

      for (j = 0 ; j < len ; j++)
      {
        uint32_pack(buf, hp[j].left) ;
        uint32_pack(buf + 4, hp[j].right) ;
        if (buffer_put(&c->b, buf, 8) < 0) goto err0 ;
        if (!posplus(c, 8)) goto err0 ;
      }
    }
  }

  if (!buffer_flush(&c->b)) goto err0 ;
  if (seek_begin(c->fd) == -1) goto err0 ;
  if (buffer_putflush(&c->b, final, 2048) < 0) goto err0 ;
  cdb_make_free(c) ;
  return 0 ;

err0:
  cdb_make_free(c) ;
  return -1 ;
}
