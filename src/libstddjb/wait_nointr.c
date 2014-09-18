/* ISC license. */

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <skalibs/djbunix.h>

pid_t wait_nointr (int *wstat)
{
  register pid_t r ;
  do
    r = wait(wstat) ;
  while ((r == (pid_t)-1) && (errno == EINTR)) ;
  return r ;
}
