/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/sysdeps.h>

#if defined(SKALIBS_HASSTRCASESTR) && !defined(SKALIBS_FLAG_REPLACE_LIBC)

#include <skalibs/nonposix.h>
#include <string.h>
#include <skalibs/bytestr.h>

unsigned int case_str (char const *haystack, char const *needle)
{
  register char *p = strcasestr(haystack, needle) ;
  return p ? p - haystack : str_len(haystack) ;
}

#else

#include <skalibs/bytestr.h>

unsigned int case_str (char const *haystack, char const *needle)
{
  unsigned int nlen = str_len(needle) ;
  register char const *p = haystack ;
  if (!nlen) return 0 ;
  for (; *p ; p++)
    if (!case_diffb(p, nlen, needle)) return p - haystack ;
  return str_len(haystack) ;
}

#endif
