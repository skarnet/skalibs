/* ISC license. */

#include <sys/types.h>
#include <skalibs/getpeereid.h>
#include <skalibs/webipc.h>

int ipc_eid (int s, unsigned int *u, unsigned int *g)
{
  uid_t dummyu ;
  gid_t dummyg ;
  if (getpeereid(s, &dummyu, &dummyg) < 0) return -1 ;
  *u = (unsigned int)dummyu ;
  *g = (unsigned int)dummyg ;
  return 0 ;
}
