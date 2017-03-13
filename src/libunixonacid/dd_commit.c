/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>
#include <skalibs/random.h>
#include <skalibs/unix-transactional.h>

static char const *mybasename (char const *s, size_t len)
{
  size_t i = len ;
  while (i--) if (s[i] == '/') return s + i + 1 ;
  return s ;
}

int dd_commit (dirdescriptor_t *dd)
{
  dirdescriptor_t zero = DIRDESCRIPTOR_ZERO ;
  size_t len = strlen(dd->lnkfn) ;
  size_t oldbase = dd->new.len ;
  size_t newlnkbase ;
  char const *lnkbn = mybasename(dd->lnkfn, len) ;
  if (!sadirname(&dd->new, dd->lnkfn, len)) return 0 ;
  if (!stralloc_catb(&dd->new, "/", 1)) goto fail ;
  if (sareadlink(&dd->new, dd->lnkfn) < 0)
  {
    size_t lnkbnbase = dd->new.len ;
    if (errno != EINVAL) goto fail ;
    if (!stralloc_cats(&dd->new, lnkbn)) goto fail ;
    if (!random_sauniquename(&dd->new, 8)) goto fail ;
    if (!stralloc_0(&dd->new)) goto fail ;
    if (rename(dd->lnkfn, dd->new.s + oldbase) < 0) goto fail ;
    /* /!\ race condition right here: there's no lnkfn in the fs */
    if (symlink(dd->new.s + lnkbnbase, dd->lnkfn) < 0) /* now that's VERY BAD if it fails */
    {
      int e = errno ;
      rename(dd->new.s + oldbase, dd->lnkfn) ; /* attempt to revert to initial situation */
      errno = e ;
      goto fail ; /* and hope for the best */
    }
  }
  if (!stralloc_0(&dd->new)) goto fail ;
  newlnkbase = dd->new.len ;
  if (!stralloc_catb(&dd->new, dd->lnkfn, len)) goto fail ;
  if (!random_sauniquename(&dd->new, 8)) goto fail ;
  if (!stralloc_0(&dd->new)) goto fail ;
  if (symlink(dd->new.s, dd->new.s + newlnkbase) < 0) goto fail ;
  if (rename(dd->new.s + newlnkbase, dd->lnkfn) < 0)
  {
    int e = errno ;
    unlink(dd->new.s + newlnkbase) ;
    errno = e ;
    goto fail ;
  }
  fd_close(dd->fd) ;
  dd->new.len = newlnkbase ;
  rm_rf_in_tmp(&dd->new, oldbase) ;
  stralloc_free(&dd->new) ;
  *dd = zero ;
  return 1 ;

 fail:
  dd->new.len = oldbase ;
  return 0 ;
}
