/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

int dd_open_read (dirdescriptor_t_ref dd, char const *path)
{
  dirdescriptor_t d = DIRDESCRIPTOR_ZERO ;
  d.fd = open_read(path) ;
  if (d.fd < 0) return 0 ;
  d.lnkfn = path ;
  *dd = d ;
  return 1 ;
}
