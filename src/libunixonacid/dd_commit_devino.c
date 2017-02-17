/* ISC license. */

#include <sys/types.h>
#include <sys/stat.h>
#include <skalibs/types.h>
#include <skalibs/unix-transactional.h>

int dd_commit_devino (dirdescriptor_t *dd, dev_t *dev, ino_t *ino)
{
  struct stat st ;
  if (fstat(dd->fd, &st) < 0) return 0 ;
  if (!dd_commit(dd)) return 0 ;
  *dev = st.st_dev ;
  *ino = st.st_ino ;
  return 1 ;
}
