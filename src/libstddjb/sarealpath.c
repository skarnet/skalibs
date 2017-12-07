/* ISC license. */

#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sarealpath (stralloc *sa, char const *path)
{
  if (sa->s)
  {
    if (!stralloc_readyplus(sa, PATH_MAX)) return -1 ;
    if (!realpath(path, sa->s + sa->len)) return -1 ;
    sa->len += strlen(sa->s + sa->len) ;
  }
  else
  {
    char *p = realpath(path, 0) ;
    if (!p) return -1 ;
    sa->s = p ;
    sa->len = strlen(p) ;
    sa->a = sa->len + 1 ;
  }
  return 0 ;
}
