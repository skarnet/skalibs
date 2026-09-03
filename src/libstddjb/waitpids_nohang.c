/* ISC license. */

#include <unistd.h>
#include <sys/wait.h>

#include <skalibs/djbunix.h>

 /*
   waitpids_nohang (defined here): only reap pids, don't touch the rest
 */

int waitpids_nohang (pid_t const *pids, size_t len, int *wstat, size_t *n)
{
  for (size_t i = 0 ; i < len ; i++)
  {
    pid_t r = waitpid_nohang(pids[i], wstat) ;
    if (r == (pid_t)-1 || r == pids[i])
    {
      *n = i ;
      return r == (pid_t)-1 ? -1 : 1 ;
    }
  }
  return 0 ;
}
