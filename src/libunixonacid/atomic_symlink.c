/* ISC license. */

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <skalibs/random.h>
#include <skalibs/unix-transactional.h>

int atomic_symlink (char const *target, char const *name, char const *suffix)
{
  {
    int e = errno ;
    if (symlink(target, name) == 0) return 1 ;
    if (errno != EEXIST) return 0 ;
    errno = e ;
  }
  {
    size_t namelen = strlen(name) ;
    size_t suffixlen = suffix ? strlen(suffix) : 25 ;
    char tmp[namelen + suffixlen + 2] ;
    memcpy(tmp, name, namelen) ;
    tmp[namelen] = ':' ;
    if (suffix)
      memcpy(tmp + namelen + 1, suffix, suffixlen + 1) ;
    else
    {
      memcpy(tmp + namelen + 1, "atomic_symlink:", 15) ;
      random_name(tmp + namelen + 16, 8) ;
      tmp[namelen + 24] = 0 ;
    }
    {
      int e = errno ;
      if (unlink(tmp) < 0 && errno != ENOENT) return 0 ;
      errno = e ;
    }
    if (symlink(target, tmp) < 0) return 0 ;
    if (rename(tmp, name) < 0)
    {
      int e = errno ;
      unlink(tmp) ;
      errno = e ;
      return 0 ;
    }
  }
  return 1 ;
}
