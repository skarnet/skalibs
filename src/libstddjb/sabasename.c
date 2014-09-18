/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sabasename (stralloc *sa, char const *s, unsigned int len)
{
  if (!len) return stralloc_catb(sa, ".", 1) ;
  while (len && (s[len-1] == '/')) len-- ;
  if (!len) return stralloc_catb(sa, "/", 1) ;
  {
    register unsigned int i = byte_rchr(s, len, '/') ;
    i = (i == len) ? 0 : i+1 ;
    return stralloc_catb(sa, s + i, len - i) ;
  }
}
