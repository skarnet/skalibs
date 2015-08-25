/* ISC license. */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <skalibs/bytestr.h>
#include <skalibs/strerr2.h>
#include <skalibs/stralloc.h>
#include <skalibs/direntry.h>
#include <skalibs/djbunix.h>

static int dircopy (char const *src, char const *dst, mode_t mode, stralloc *tmp)
{
  unsigned int tmpbase = tmp->len ;
  unsigned int maxlen = 0 ;
  {
    DIR *dir = opendir(src) ;
    if (!dir) return 0 ;
    for (;;)
    {
      direntry *d ;
      register unsigned int n ;
      errno = 0 ;
      d = readdir(dir) ;
      if (!d) break ;
      if (d->d_name[0] == '.')
        if (((d->d_name[1] == '.') && !d->d_name[2]) || !d->d_name[1])
          continue ;
      n = str_len(d->d_name) ;
      if (n > maxlen) maxlen = n ;
      if (!stralloc_catb(tmp, d->d_name, n+1)) break ;
    }
    if (errno)
    {
      int e = errno ;
      dir_close(dir) ;
      errno = e ;
      goto err ;
    }
    dir_close(dir) ;
  }

  if (mkdir(dst, S_IRWXU) < 0)
  {
    struct stat st ;
    if (errno != EEXIST) goto err ;
    if (stat(dst, &st) < 0) goto err ;
    if (!S_ISDIR(st.st_mode)) { errno = ENOTDIR ; goto err ; }
  }
  {
    unsigned int srclen = str_len(src) ;
    unsigned int dstlen = str_len(dst) ;
    unsigned int i = tmpbase ;
    char srcbuf[srclen + maxlen + 2] ;
    char dstbuf[dstlen + maxlen + 2] ;
    byte_copy(srcbuf, srclen, src) ;
    byte_copy(dstbuf, dstlen, dst) ;
    srcbuf[srclen] = '/' ;
    dstbuf[dstlen] = '/' ;
    while (i < tmp->len)
    {
      register unsigned int n = str_len(tmp->s + i) + 1 ;
      byte_copy(srcbuf + srclen + 1, n, tmp->s + i) ;
      byte_copy(dstbuf + dstlen + 1, n, tmp->s + i) ;
      i += n ;
      hiercopy_tmp(srcbuf, dstbuf, tmp) ;
    }
  }
  if (chmod(dst, mode) < 0) goto err ;
  tmp->len = tmpbase ;
  return 1 ;
err:
  tmp->len = tmpbase ;
  return 0 ;
}

int hiercopy_tmp (char const *src, char const *dst, stralloc *tmp)
{
  struct stat st ;
  if (lstat(src, &st) < 0) return 0 ;
  if (S_ISREG(st.st_mode))
  {
    if (!filecopy_unsafe(src, dst, st.st_mode)) return 0 ;
  }
  else if (S_ISDIR(st.st_mode))
  {
    if (!dircopy(src, dst, st.st_mode, tmp)) return 0 ;
  }
  else if (S_ISFIFO(st.st_mode))
  {
    if (mkfifo(dst, st.st_mode) < 0) return 0 ;
  }
  else if (S_ISLNK(st.st_mode))
  {
    unsigned int tmpbase = tmp->len ;
    if (sareadlink(tmp, src) < 0) return 0 ;
    if (!stralloc_0(tmp))
    {
      tmp->len = tmpbase ;
      return 0 ;
    }
    if (symlink(tmp->s + tmpbase, dst) < 0)
    {
      tmp->len = tmpbase ;
      return 0 ;
    }
    tmp->len = tmpbase ;
  }
  else if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode) || S_ISSOCK(st.st_mode))
  {
    if (mknod(dst, st.st_mode, st.st_rdev) < 0) return 0 ;
  }
  else return (errno = ENOTSUP, 0) ;
  lchown(dst, st.st_uid, st.st_gid) ;
  if (!S_ISLNK(st.st_mode)) chmod(dst, st.st_mode) ;
  return 1 ;
}
