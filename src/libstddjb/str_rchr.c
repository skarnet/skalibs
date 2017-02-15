/* ISC license. */

#include <sys/types.h>
#include <string.h>
#include <skalibs/bytestr.h>

size_t str_rchr (register char const *s, int c)
{
  register char *p = strrchr(s, c) ;
  return p ? p - s : strlen(s) ;
}

