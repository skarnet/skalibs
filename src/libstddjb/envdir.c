/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/env.h>
#include <skalibs/direntry.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

#define MAXVARSIZE 4095

int envdir_internal (char const *path, stralloc *modifs, unsigned int options, char nullis)
{
  char buf[MAXVARSIZE + 1] ;
  unsigned int n = 0 ;
  unsigned int pathlen = str_len(path) ;
  unsigned int modifbase = modifs->len ;
  int wasnull = !modifs->s ;
  DIR *dir ;
  if (!nullis) return (errno = EINVAL, -1) ;
  dir = opendir(path) ;
  if (!dir) return -1 ;
  for (;;)
  {
    direntry *d ;
    unsigned int len ;
    register int r ;
    errno = 0 ;
    d = readdir(dir) ;
    if (!d) break ;
    if (d->d_name[0] == '.') continue ;
    len = str_len(d->d_name) ;
    if (str_chr(d->d_name, '=') < len) continue ;
    {
      char tmp[pathlen + len + 2] ;
      byte_copy(tmp, pathlen, path) ;
      tmp[pathlen] = '/' ;
      byte_copy(tmp + pathlen + 1, len + 1, d->d_name) ;
      r = openreadnclose(tmp, buf, MAXVARSIZE) ;
    }
    if (r < 0)
    {
      if (errno == ENOENT) errno = EIDRM ;
      goto err ;
    }
    else if (r > 0)
    {
      if (options & SKALIBS_ENVDIR_VERBATIM)
      {
        if (!(options & SKALIBS_ENVDIR_NOCHOMP) && (buf[r-1] == '\n')) r-- ;
      }
      else
      {
        r = byte_chr(buf, r, '\n') ;
        if (!(options & SKALIBS_ENVDIR_NOCHOMP))
        {
          while (r--) if ((buf[r] != ' ') && (buf[r] != '\t') && (buf[r] != '\r')) break ;
          r++ ;
        }
      }
      {
        register unsigned int i = 0 ;
        for (; i < (unsigned int)r ; i++) if (!buf[i]) buf[i] = nullis ;
      }
      buf[r++] = 0 ;
      if (!env_addmodif(modifs, d->d_name, buf)) goto err ;
    }
    else if (!env_addmodif(modifs, d->d_name, 0)) goto err ;
    n++ ;
  }
  if (errno) goto err ;
  dir_close(dir) ;
  return n ;

 err:
  {
    register int e = errno ;
    dir_close(dir) ;
    if (wasnull) stralloc_free(modifs) ; else modifs->len = modifbase ;
    errno = e ;
    return -1 ;
  }
}
