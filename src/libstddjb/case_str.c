/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSTRCASESTR

#include <skalibs/nonposix.h>
#include <string.h>
#include <skalibs/bytestr.h>

size_t case_str (char const *haystack, char const *needle)
{
  register char *p = strcasestr(haystack, needle) ;
  return p ? p - haystack : strlen(haystack) ;
}

#else

#include <sys/types.h>
#include <string.h>
#include <skalibs/bytestr.h>

size_t case_str (char const *haystack, char const *needle)
{
  size_t nlen = strlen(needle) ;
  char const *p = haystack ;
  if (!nlen) return 0 ;
  for (; *p ; p++)
    if (!case_diffb(p, nlen, needle)) return p - haystack ;
  return strlen(haystack) ;
}

#endif
