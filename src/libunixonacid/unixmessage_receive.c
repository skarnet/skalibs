/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>
#include <skalibs/cbuffer.h>
#include <skalibs/error.h>
#include <skalibs/stralloc.h>
#include <skalibs/uint.h>
#include <skalibs/unixmessage.h>

int unixmessage_receive (unixmessage_receiver_t *b, unixmessage_t *m)
{
  if (b->data.len == b->mainlen)
  {
    char pack[sizeof(unsigned int) << 1] ;
    if (buffer_len(&b->mainb) < sizeof(unsigned int) << 1)
    {
      register int r = sanitize_read(buffer_fill(&b->mainb)) ;
      if (r <= 0) return r ;
      if (r < sizeof(unsigned int) << 1) return (errno = EWOULDBLOCK, 0) ;
    }
    buffer_getnofill(&b->mainb, pack, sizeof(unsigned int) << 1) ;
    uint_unpack_big(pack, &b->mainlen) ;
    uint_unpack_big(pack + sizeof(unsigned int), &b->auxlen) ;
    if (b->auxlen > UNIXMESSAGE_MAXFDS) return (errno = EPROTO, -1) ;
    b->auxlen *= sizeof(int) ;
    if (!stralloc_ready(&b->data, b->mainlen)) return -1 ;
    b->data.len = 0 ;
    b->auxw = cbuffer_get(&b->auxb, (char *)b->fds, b->auxlen) ;
  }
  {
    register int r = buffer_getall(&b->mainb, b->data.s, b->mainlen, &b->data.len) ;
    if (r <= 0) return r ;
  }
  if (b->auxw < b->auxlen)
    b->auxw += cbuffer_get(&b->auxb, (char *)b->fds, b->auxlen - b->auxw) ;
  if (b->auxw < b->auxlen) return (errno = EPROTO, -1) ;
  m->s = b->data.s ;
  m->len = b->data.len ;
  m->fds = b->fds ;
  m->nfds = b->auxlen / sizeof(int) ;
  return 1 ;
}
