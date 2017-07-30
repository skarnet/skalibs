/* ISC license. */

#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/socket.h>
#include <skalibs/ip46.h>

int socket_deadlineconnstamp46 (int s, ip46_t const *i, uint16_t port, tain_t const *deadline, tain_t *stamp)
{
  int e = errno ;
  if (socket_connect46(s, i, port) >= 0) return 1 ;
  if (!error_isagain(errno) && !error_isalready(errno)) return 0 ;
  errno = e ;
  return socket_waitconn(s, deadline, stamp) ;
}
