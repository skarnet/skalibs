/* ISC license. */

#include <skalibs/sysdeps.h>

#if defined(SKALIBS_HASPOSIXSPAWN) && defined(SKALIBS_HASPOSIXSPAWNEARLYRETURN)

#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>
#include "child_spawn-internal.h"

pid_t child_spawn_workaround (pid_t pid, int const *p)
{
  siginfo_t si ;
  int e ;
  ssize_t r ;
  char c ;

  fd_close(p[1]) ;
  r = fd_read(p[0], &c, 1) ;
  fd_close(p[0]) ;
  if (r == -1) return 0 ;
  if (r) return (errno = EILSEQ, 0) ;  /* child wrote, wtf */

  do e = waitid(P_PID, pid, &si, WEXITED | WNOHANG | WNOWAIT) ;
  while (e == -1 && errno == EINTR) ;
  if (e == -1) return pid ;  /* we're in trouble, but don't leak a child */
  if (!si.si_pid) return pid ;  /* child is running */
  if (si.si_code != CLD_EXITED || si.si_status != 127) return pid ; /* child died after execve(), let caller handle it */
  /*
    child exited 127, so either execve() failed, which is what we want to catch,
    or it raced like a mofo, execve()d and then exited 127 on its own, in which
    case, tough luck, it never existed.
  */
  wait_pid(pid, 0) ;
  return (errno = 0, 0) ;
}

#else

 /* avoid empty TUs */

extern int skalibs_child_spawn_workaround_dummy_ ;

#endif
