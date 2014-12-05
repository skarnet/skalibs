/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/siovec.h>
#include <skalibs/stralloc.h>
#include <skalibs/skamisc.h>

int skagetln_nofill (buffer *b, stralloc *sa, char sep)
{
  siovec_t v[2] ;
  unsigned int pos ;
  int r ;
  buffer_rpeek(b, v) ;
  pos = siovec_bytechr(v, 2, sep) ;
  r = pos < buffer_len(b) ; pos += r ;
  if (!stralloc_readyplus(sa, pos)) return -1 ;
  buffer_getnofill(b, sa->s + sa->len, pos) ; sa->len += pos ;
  return r ;
}
