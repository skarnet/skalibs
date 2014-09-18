/* ISC license. */

#include <sys/types.h>
#include <skalibs/djbunix.h>

int waitn (pid_t *pids, unsigned int n)
{
  while (n)
  {
    int wstat ;
    register unsigned int i = 0 ;
    register pid_t pid = wait_nointr(&wstat) ;
    if (pid < 0) return 0 ;
    for (; i < n ; i++) if (pid == pids[i]) break ;
    if (i < n) pids[i] = pids[--n] ;
  }
  return 1 ;
}
