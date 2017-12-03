/* ISC license. */

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
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
    size_t suffixlen = suffix ? strlen(suffix) : 8 ;
    char tmp[namelen + suffixlen + 2] ;
    memcpy(tmp, name, namelen) ;
    tmp[namelen] = ':' ;
    if (suffix)
      memcpy(tmp + namelen + 1, suffix, suffixlen + 1) ;
    else
    {
      random_name(tmp + namelen + 1, 8) ;
      tmp[namelen + 9] = 0 ;
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
