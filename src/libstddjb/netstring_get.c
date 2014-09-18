/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/uint.h>
#include <skalibs/bytestr.h>
#include <skalibs/buffer.h>
#include <skalibs/cbuffer.h>
#include <skalibs/error.h>
#include <skalibs/stralloc.h>
#include <skalibs/netstring.h>

int netstring_okeof (buffer *b, unsigned int w)
{
  return (errno == EPIPE) && !w && buffer_isempty(b) ? (errno = 0, 1) : 0 ;
}

int netstring_get (buffer *b, stralloc *sa, unsigned int *state)
{
  if (!*state)
  {
    unsigned int n ;
    unsigned int len ;
    char buf[UINT_FMT] ;
    if (b->c.a < UINT_FMT+1) return (errno = EINVAL, -1) ;
    for (;;)
    {
      register int r ;
      len = buffer_getnofill(b, buf, UINT_FMT) ;
      n = byte_chr(buf, len, ':') ;  /* XXX: accepts :, as a valid netstring */
      if (n >= UINT_FMT)
      {
        buffer_unget(b, len) ;
        return (errno = EPROTO, -1) ;
      }
      if (n < len) break ;
      buffer_unget(b, len) ;
      r = sanitize_read(buffer_fill(b)) ;
      if (r <= 0) return r ;
    }
    buffer_unget(b, len - n - 1) ;
    if (!n || n != uint_scan(buf, &len)) return (errno = EPROTO, -1) ;
    if (!stralloc_readyplus(sa, len + 1)) return -1 ;
    *state = len + 1 ;
  }
  {
    unsigned int w = 0 ;
    register int r = buffer_getall(b, sa->s + sa->len, *state, &w) ;
    sa->len += w ;
    *state -= w ;
    if (r <= 0) return r ;
  }
  return (sa->s[--sa->len] == ',') ? 1 : (errno = EPROTO, -1) ;
}
