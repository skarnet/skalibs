/* ISC license. */

/* MT-unsafe */

#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

char *basename (char *s)
{
  static stralloc basename_sa = STRALLOC_ZERO ;
  static char dot0[2] = "." ;
  char *dot = dot0 ;
  if (!s) return dot ;
  basename_sa.len = 0 ;
  if (!sabasename(&basename_sa, s, str_len(s))) return 0 ;
  if (!stralloc_0(&basename_sa)) return 0 ;
  return basename_sa.s ;
}
