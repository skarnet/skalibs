/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/error.h>
#include <skalibs/webipc.h>

int ipc_bind (int s, char const *p)
{
  struct sockaddr_un sa ;
  register unsigned int l = str_len(p) ;
  if (l > IPCPATH_MAX) return (errno = EPROTO, -1) ;
  byte_zero((char *)&sa, sizeof sa) ;
  sa.sun_family = AF_UNIX ;
  byte_copy(sa.sun_path, l+1, p) ;
  return bind(s, (struct sockaddr *)&sa, sizeof sa) ;
}
