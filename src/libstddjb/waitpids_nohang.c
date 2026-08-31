/* ISC license. */

#include <sys/wait.h>
#include <skalibs/djbunix.h>

 /*
   waitpids_nohang (defined here): only reap pids, don't touch the rest
 */

int waitpids_nohang (pid_t const *pids, unsigned int len, int *wstat)
{
  for (unsigned int i = 0 ; i < len ; i++)
  {
    pid_t r = waitpid_nohang(pids[i], wstat) ;
    if (r == -1) return -1-i ;
    else if (r == pids[i]) return 1+i ;
  }
  return 0 ;
}
