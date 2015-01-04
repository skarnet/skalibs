/* ISC license. */

#include <errno.h>
#include <skalibs/djbunix.h>
#include <skalibs/unixmessage.h>

void unixmessage_drop (unixmessage_t const *m)
{
  int e = errno ;
  register unsigned int i = 0 ;
  for (; i < m->nfds ; i++) fd_close(m->fds[i]) ;
  errno = e ;
}
