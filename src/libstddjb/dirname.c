/* ISC license. */

/* MT-unsafe */

#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

char *dirname (char *s)
{
  static stralloc dirname_sa = STRALLOC_ZERO ;
  static char dot0[2] = "." ;
  char *dot = dot0 ;
  if (!s) return dot ;
  dirname_sa.len = 0 ;
  if (!sadirname(&dirname_sa, s, str_len(s))) return 0 ;
  if (!stralloc_0(&dirname_sa)) return 0 ;
  return dirname_sa.s ;
}
