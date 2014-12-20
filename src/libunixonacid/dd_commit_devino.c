/* ISC license. */

#include <sys/types.h>
#include <sys/stat.h>
#include <skalibs/uint64.h>
#include <skalibs/unix-transactional.h>

int dd_commit_devino (dirdescriptor_t *dd, uint64 *dev, uint64 *ino)
{
  struct stat st ;
  if (fstat(dd->fd, &st) < 0) return 0 ;
  if (!dd_commit(dd)) return 0 ;
  *dev = (uint64)st.st_dev ;
  *ino = (uint64)st.st_ino ;
  return 1 ;
}
