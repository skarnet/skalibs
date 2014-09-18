/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/bytestr.h>

#ifdef SKALIBS_FLAG_REPLACE_LIBC

/* Very naive implementation, but it's small. */

unsigned int str_strn (char const *haystack, unsigned int hlen, char const *needle, unsigned int nlen)
{
  register unsigned int i = 0 ;
  if (!nlen) return 0 ;
  if (hlen < nlen) return hlen ;
  hlen -= nlen ;
  for (; i <= hlen ; i++)
    if (!byte_diff(haystack+i, nlen, needle)) return i ;
  return hlen+nlen ;
}

#else

#include <string.h>

unsigned int str_strn (char const *haystack, unsigned int hlen, char const *needle, unsigned int nlen)
{
  char haystack2[hlen+1] ;
  char needle2[nlen+1] ;
  register char *p ;
  byte_copy(haystack2, hlen, haystack) ; haystack2[hlen] = 0 ;
  byte_copy(needle2, nlen, needle) ; needle2[nlen] = 0 ;
  p = strstr(haystack2, needle2) ;
  return p ? p - haystack2 : hlen ;
}

#endif
