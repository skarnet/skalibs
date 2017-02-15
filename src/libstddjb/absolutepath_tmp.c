/* ISC license. */

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sarealpath_tmp (stralloc *sa, char const *path, stralloc *tmp)
{
  size_t tmpbase = tmp->len ;
  size_t base = sa->len ;
  unsigned int loop = 48 ;
  int fdhere ;
  int wasnull = !sa->s ;

  if (!path) return (errno = EINVAL, -1) ;
  if (!stralloc_cats(sa, path)) return -1 ;
  fdhere = open_read(".") ;
  if (fdhere == -1)
  {
    if (wasnull) stralloc_free(sa) ; else sa->len = base ;
    return -1 ;
  }

  do
  {
    tmp->len = tmpbase ;
    if (!loop--) { errno = ELOOP ; goto err ; }
    if (!sadirname(tmp, sa->s + base, sa->len - base)
     || !stralloc_0(tmp)
     || (chdir(tmp->s + tmpbase) == -1))
      goto err ;
    tmp->len = tmpbase ;
    if (!sabasename(tmp, sa->s + base, sa->len - base)
     || !stralloc_0(tmp)) goto err ;
    sa->len = base ;
  }
  while (sareadlink(sa, tmp->s + tmpbase) >= 0) ;

  if ((errno != EINVAL)
   || (sagetcwd(sa) == -1)
   || ((sa->len > base + 1) && !stralloc_catb(sa, "/", 1))
   || ((--tmp->len > tmpbase) && (tmp->s[tmpbase] != '/') && !stralloc_catb(sa, tmp->s + tmpbase, tmp->len - tmpbase)))
    goto err ;

  tmp->len = tmpbase ;
  fd_chdir(fdhere) ;
  fd_close(fdhere) ;
  return 0 ;

err:
  {
    register int e = errno ;
    tmp->len = tmpbase ;
    fd_chdir(fdhere) ;
    fd_close(fdhere) ;
    if (wasnull) stralloc_free(sa) ; else sa->len = base ;
    errno = e ;
  }
  return -1 ;
}
