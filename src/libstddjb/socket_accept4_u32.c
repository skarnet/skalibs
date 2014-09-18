/* ISC license. */

#include <skalibs/uint16.h>
#include <skalibs/uint32.h>
#include <skalibs/socket.h>

int socket_accept4_internal_u32 (int s, uint32 *ip, uint16 *port, unsigned int options)
{
  char pack[4] ;
  register int r = socket_accept4_internal(s, pack, port, options) ;
  if (r >= 0) uint32_unpack_big(pack, ip) ;
  return r ;
}
