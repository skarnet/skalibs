/* ISC license. */

#include <sys/types.h>
#include <skalibs/djbunix.h>

pid_t wait_pid_nohang (pid_t pid, int *wstat)
{
  int w = 0 ;
  register pid_t r = 0 ;
  while (r != pid)
  {
    r = wait_nohang(&w) ;
    if (!r || (r == (pid_t)-1)) return (int)r ;
  }
  *wstat = w ;
  return r ;
}
