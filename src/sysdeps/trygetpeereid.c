/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <sys/types.h>
#include <unistd.h>

int main (void)
{
  uid_t uid ;
  gid_t gid ;
  int s = 0 ;
  return getpeereid(s, &uid, &gid) ;
}
