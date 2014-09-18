/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/djbtime.h>

unsigned int localtmn_fmt (char *s, localtmn_t const *l)
{
  char *p = s ;
  p += localtm_fmt(p, &l->tm) ; *p++ = '.' ;
  uint320_fmt(p, l->nano, 9) ; p += 9 ;
  return p - s ;
}
