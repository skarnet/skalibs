/* ISC license. */

#include <sys/types.h>
#include <skalibs/djbunix.h>

int waitn_reap (pid_t *pids, unsigned int len)
{
  unsigned int n = 0 ;
  while (len)
  {
    int w ;
    register int r = wait_pids_nohang(pids, len, &w) ;
    if (r < 0) return r ;
    else if (!r) break ;
    pids[r-1] = pids[--len] ;
    n++ ;
  }
  return (int)n ;
}
