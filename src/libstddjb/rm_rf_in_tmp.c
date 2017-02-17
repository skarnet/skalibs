/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <skalibs/stralloc.h>
#include <skalibs/direntry.h>
#include <skalibs/djbunix.h>

static int rmstarindir (DIR *dir, stralloc *tmp, size_t ipos) /* WARNING: closes dir */
{
  size_t tmpbase = tmp->len ;
  for (;;)
  {
    direntry *d ;
    errno = 0 ;
    d = readdir(dir) ;
    if (!d) break ;
    if (d->d_name[0] == '.')
      if (((d->d_name[1] == '.') && (d->d_name[2] == 0)) || (d->d_name[1] == 0))
        continue ;
    if (!stralloc_cats(tmp, d->d_name) || !stralloc_0(tmp)) goto closeanderr ;
  }
  if (errno) goto closeanderr ;
  dir_close(dir) ;

  {
    size_t tmpstop = tmp->len ;
    size_t fnbase = strlen(tmp->s + ipos) ;
    size_t i = tmpbase ;
    if (!stralloc_readyplus(tmp, fnbase+1)) goto err ;
    stralloc_catb(tmp, tmp->s + ipos, fnbase) ;
    stralloc_catb(tmp, "/", 1) ;
    fnbase = tmp->len ;
    for (; i < tmpstop ; i += tmp->len - fnbase)
    {
      size_t n = strlen(tmp->s + i) ;
      tmp->len = fnbase ;
      if (!stralloc_readyplus(tmp, n+1)) goto err ;
      stralloc_catb(tmp, tmp->s + i, n+1) ;
      if (rm_rf_in_tmp(tmp, tmpstop) == -1) goto err ;
    }
  }
  tmp->len = tmpbase ;
  return 0 ;

closeanderr:
  {
    int e = errno ;
    dir_close(dir) ;
    errno = e ;
  }
err:
  tmp->len = tmpbase ;
  return -1 ;
}

int rm_rf_in_tmp (stralloc *tmp, size_t ipos)
{
  if (unlink(tmp->s + ipos) == 0) return 0 ;
  if (errno == ENOENT) return 0 ;
  if ((errno != EISDIR) && (errno != EPERM)) return -1 ;
  {
    int h = (errno == EPERM) ;
    DIR *dir = opendir(tmp->s + ipos) ;
    if (!dir)
    {
      if (h && (errno == ENOTDIR)) errno = EPERM ;
      return -1 ;
    }
    if (rmstarindir(dir, tmp, ipos) == -1) return -1 ;
  }
  return rmdir(tmp->s + ipos) ;
}

int rmstar_tmp (char const *dirname, stralloc *tmp)
{
  size_t tmpbase = tmp->len ;
  if (!stralloc_cats(tmp, dirname)) return -1 ;
  if (!stralloc_0(tmp)) goto err ;
  {
    DIR *dir = opendir(dirname) ;
    if (!dir) goto err ;
    if (rmstarindir(dir, tmp, tmpbase) == -1) goto err ;
  }
  tmp->len = tmpbase ;
  return 0 ;

err:
  tmp->len = tmpbase ;
  return -1 ;
}
