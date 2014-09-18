/* ISC license. */

#include <limits.h>
#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

#ifndef PATH_MAX
# define PATH_MAX 4095
#endif

char *realpath_tmp (char const *name, char *buf, stralloc *tmp)
{
  unsigned int tmpbase = tmp->len ;
  if (sarealpath(tmp, name) == -1) return (char *)0 ;
  if (tmp->len - tmpbase > PATH_MAX)
  {
    tmp->len = tmpbase ;
    return (errno = ENAMETOOLONG, (char *)0) ;
  }
  byte_copy(buf, tmp->len - tmpbase, tmp->s + tmpbase) ;
  buf[tmp->len - tmpbase] = 0 ;
  tmp->len = tmpbase ;
  return buf ;
}
