/* ISC license. */

#include <errno.h>
#include <skalibs/direntry.h>

int dir_close (DIR *dir)
{
  register unsigned int done = 0 ;
doit:
  done++ ;
  if (!closedir(dir)) return 0 ;
  if (errno == EINTR) goto doit ;
  return ((errno == EBADF) && (done > 1)) ? 0 : -1 ;
}
