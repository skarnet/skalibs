/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <skalibs/bytestr.h>
#include <skalibs/webipc.h>

int ipc_local (int s, char *p, unsigned int l, int *trunc)
{
  struct sockaddr_un sa ;
  socklen_t dummy = sizeof sa ;
  byte_zero((char *)&sa, sizeof sa) ;
  if (getsockname(s, (struct sockaddr *)&sa, &dummy) == -1) return -1 ;
  dummy = byte_chr(sa.sun_path, dummy, 0) ;
  *trunc = 1 ;
  if (!l) return 0 ;
  if (l < (dummy + 1)) dummy = l - 1 ;
  else *trunc = 0 ;
  byte_copy(p, dummy, sa.sun_path) ;
  p[dummy] = 0 ;
  return 0 ;
}
