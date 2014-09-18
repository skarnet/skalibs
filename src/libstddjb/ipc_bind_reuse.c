/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <unistd.h>
#include <skalibs/webipc.h>

int ipc_bind_reuse (int s, char const *p)
{
  unsigned int opt = 1 ;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt) ;
  unlink(p) ;
  return ipc_bind(s, p) ;
}
