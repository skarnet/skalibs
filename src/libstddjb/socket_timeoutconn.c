/* ISC license. */

#include <skalibs/uint16.h>
#include <skalibs/tai.h>
#include <skalibs/socket.h>

int socket_timeoutconn (int s, char const *ip, uint16 port, unsigned int timeout)
{
  tain_t stamp, deadline ;
  tain_now(&stamp) ;
  tain_addsec(&deadline, &stamp, timeout) ;
  return socket_deadlineconnstamp4(s, ip, port, &deadline, &stamp) ;
}
