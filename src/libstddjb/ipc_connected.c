/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/webipc.h>

int ipc_connected (int s)
{
  struct sockaddr_un sa ;
  socklen_t dummy = sizeof sa ;
  if (getpeername(s, (struct sockaddr *)&sa, &dummy) == -1)
  {
    char ch ;
    fd_read(s, &ch, 1) ; /* sets errno */
    return 0 ;
  }
  return 1 ;
}
