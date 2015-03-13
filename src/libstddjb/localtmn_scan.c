/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/djbtime.h>

unsigned int localtmn_scan (char const *s, localtmn_t *l)
{
  localtmn_t m ;
  unsigned int n = localtm_scan(s, &m.tm) ;
  if (!n) return 0 ;
  s += n ;
  if (*s++ != '.') m.nano = 0 ;
  else
  {
    register unsigned int b = uint32_scan(s, &m.nano) ;
    if (!b) return 0 ;
    n += b ;
  }
  *l = m ;
  return n ;
}
