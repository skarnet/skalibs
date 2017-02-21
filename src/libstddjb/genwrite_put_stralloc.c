/* ISC license. */

#include <sys/types.h>
#include <skalibs/stralloc.h>
#include <skalibs/genwrite.h>

ssize_t genwrite_put_stralloc (void *target, char const *s, size_t len)
{
  return stralloc_catb((stralloc *)target, s, len) ? (ssize_t)len : -1 ;
}
