/* ISC license. */

#include <errno.h>
#include <time.h>
#include <skalibs/djbtime.h>
#include <skalibs/uint.h>

unsigned int localtm_scan (char const *s, struct tm *l)
{
  struct tm ll = { .tm_isdst = -1 } ;
  unsigned int n = 0 ; unsigned int u ;
  register unsigned int i = uint_scan(s+n, &u) ;
  if (!i) goto fail ; n += i ;
  if (u < 1900) goto fail ; u -= 1900 ; ll.tm_year = u ;
  if (s[n++] != '-') goto fail ;
  i = uint_scan(s+n, &u) ;
  if (!i) goto fail ; n += i ;
  if (!u || (u > 12)) goto fail ; u-- ; ll.tm_mon = u ;
  if (s[n++] != '-') goto fail ;
  i = uint_scan(s+n, &u) ;
  if (!i) goto fail ; n += i ;
  if (!u || (u > 31)) goto fail ; ll.tm_mday = u ;
  if ((s[n] != ' ') && (s[n] != 'T')) goto fail ; n++ ;
  i = uint_scan(s+n, &u) ;
  if (!i) goto fail ; n += i ;
  if (u > 23) goto fail ; ll.tm_hour = u ;
  if (s[n++] != ':') goto fail ;
  i = uint_scan(s+n, &u) ;
  if (!i) goto fail ; n += i ;
  if (u > 59) goto fail ; ll.tm_min = u ;
  if (s[n++] != ':') goto fail ;
  i = uint_scan(s+n, &u) ;
  if (!i) goto fail ; n += i ;
  if (u > 60) goto fail ; ll.tm_sec = u ;
  if (mktime(&ll) == (time_t)-1) goto fail ;
  *l = ll ;
  return n ;
 fail:
  return (errno = EINVAL, 0) ;
}
