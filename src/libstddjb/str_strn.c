/* ISC license. */

#include <sys/types.h>
#include <string.h>
#include <skalibs/bytestr.h>

size_t str_strn (char const *haystack, size_t hlen, char const *needle, size_t nlen)
{
  char haystack2[hlen+1] ;
  char needle2[nlen+1] ;
  char *p ;
  byte_copy(haystack2, hlen, haystack) ; haystack2[hlen] = 0 ;
  byte_copy(needle2, nlen, needle) ; needle2[nlen] = 0 ;
  p = strstr(haystack2, needle2) ;
  return p ? p - haystack2 : hlen ;
}
