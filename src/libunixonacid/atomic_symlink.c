/* ISC license. */

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include <skalibs/posixplz.h>
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
    size_t suffixlen = suffix ? strlen(suffix) + 1 : 0 ;
    char tmp[namelen + suffixlen + 8] ;
    memcpy(tmp, name, namelen) ;
    if (suffix)
    {
      tmp[namelen] = ':' ;
      memcpy(tmp + namelen + 1, suffix, suffixlen - 1) ;
    }
    memcpy(tmp + namelen + suffixlen, ":XXXXXX", 7) ;
    tmp[namelen + suffixlen + 7] = 0 ;
    if (mkltemp(target, tmp) == -1) return 0 ;
    if (rename(tmp, name) < 0)
    {
      unlink_void(tmp) ;
      return 0 ;
    }
  }
  return 1 ;
}
