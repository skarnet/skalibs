/* ISC license. */

#include <sys/types.h>
#include <errno.h>
#include <skalibs/uint64.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/bytestr.h>
#include <skalibs/buffer.h>
#include <skalibs/cbuffer.h>
#include <skalibs/error.h>
#include <skalibs/stralloc.h>
#include <skalibs/netstring.h>

int netstring_okeof (buffer *b, size_t w)
{
  return (errno == EPIPE) && !w && buffer_isempty(b) ? (errno = 0, 1) : 0 ;
}

ssize_t netstring_get (buffer *b, stralloc *sa, size_t *state)
{
  if (!*state)
  {
    size_t n ;
    size_t len ;
    char buf[UINT64_FMT] ;
    if (b->c.a < UINT64_FMT+1) return (errno = EINVAL, -1) ;
    for (;;)
    {
      register int r ;
      len = buffer_getnofill(b, buf, UINT64_FMT) ;
      n = byte_chr(buf, len, ':') ;  /* XXX: accepts :, as a valid netstring */
      if (n >= UINT64_FMT)
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
    if (!n || n != uint64_scan(buf, &len)) return (errno = EPROTO, -1) ;
    if (!stralloc_readyplus(sa, len + 1)) return -1 ;
    *state = len + 1 ;
  }
  {
    size_t w = 0 ;
    register ssize_t r = buffer_getall(b, sa->s + sa->len, *state, &w) ;
    sa->len += w ;
    *state -= w ;
    if (r <= 0) return r ;
  }
  return (sa->s[--sa->len] == ',') ? 1 : (errno = EPROTO, -1) ;
}
