/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/skamisc.h>

int string_unquote (char *d, unsigned int *w, char const *s, unsigned int len, unsigned int *r)
{
  if (!len-- || (*s++ != '"')) return (errno = EINVAL, 0) ;
  {
    unsigned int rr, ww ;
    char tmp[len] ;
    if (!string_unquote_withdelim(tmp, &ww, s, len, &rr, "\"", 1)) return 0 ;
    if (rr == len) return (errno = EPIPE, 0) ;
    byte_copy(d, ww, tmp) ;
    *w = ww ;
    *r = rr + 2 ;
  }
  return 1 ;
}
