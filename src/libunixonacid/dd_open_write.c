/* ISC license. */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>
#include <skalibs/random.h>
#include <skalibs/unix-transactional.h>

int dd_open_write (dirdescriptor_t *dd, char const *lnkfn, unsigned int mode)
{
  dirdescriptor_t d = DIRDESCRIPTOR_ZERO ;
  d.lnkfn = lnkfn ;
  if (!stralloc_cats(&d.new, lnkfn)) return 0 ;
  if (random_sauniquename(&d.new, 8) < 0) goto fail ;
  if (!stralloc_0(&d.new)) goto fail ;
  if (mkdir(d.new.s, mode) < 0) goto fail ;
  d.fd = open_read(d.new.s) ;
  if (d.fd < 0)
  {
    register int e = errno ;
    rmdir(d.new.s) ;
    errno = e ;
    goto fail ;
  }
  *dd = d ;
  return 1 ;

 fail:
  stralloc_free(&d.new) ;
  return 0 ;
}
