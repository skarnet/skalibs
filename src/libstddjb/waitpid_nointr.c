/* ISC license. */

#include <sys/wait.h>
#include <errno.h>
#include <skalibs/djbunix.h>

pid_t waitpid_nointr (pid_t pid, int *wstat, int flags)
{
  pid_t r ;
  do r = waitpid(pid, wstat, flags) ;
  while ((r == (pid_t)-1) && (errno == EINTR)) ;
  return r ;
}
