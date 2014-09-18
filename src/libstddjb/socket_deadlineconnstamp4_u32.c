/* ISC license. */

#include <skalibs/uint16.h>
#include <skalibs/uint32.h>
#include <skalibs/tai.h>
#include <skalibs/socket.h>

int socket_deadlineconnstamp4_u32 (int s, uint32 ip, uint16 port, tain_t const *deadline, tain_t *stamp)
{
  char pack[4] ;
  uint32_pack_big(pack, ip) ;
  return socket_deadlineconnstamp4(s, pack, port, deadline, stamp) ;
}
