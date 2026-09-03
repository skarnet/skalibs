/* ISC license. */

#include <unistd.h>
#include <sys/wait.h>

#include <skalibs/djbunix.h>

 /*
   waitpids: blocking wait, don't reap anything unlisted
 */

size_t waitpids (pid_t const *pids, size_t len, int *wstat)
{
  for (size_t i = 0 ; i < len ; i++)
  {
    pid_t r = wait_pid(pids[i], wstat) ;
    if (r == (pid_t)-1) return i ;
  }
  return len ;
}
