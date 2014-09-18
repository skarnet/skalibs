/* ISC license. */

#include <skalibs/sysdeps.h>
#include <sys/types.h>
#include <errno.h>

#ifdef SKALIBS_HASPOSIXSPAWN

#include <spawn.h>
#include <stdlib.h>
#include <skalibs/config.h>
#include <skalibs/env.h>

pid_t child_spawn0 (char const *prog, char const *const *argv, char const *const *envp)
{
  pid_t pid ;
  int e ;
  int haspath = !!env_get("PATH") ;
  if (!haspath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) < 0)) return 0 ;
  e = posix_spawnp(&pid, prog, 0, 0, (char *const *)argv, (char *const *)envp) ;
  if (!haspath) unsetenv("PATH") ;
  return e ? (errno = e, 0) : pid ;
}

#else

#include <unistd.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>

pid_t child_spawn0 (char const *prog, char const *const *argv, char const *const *envp)
{
  int e ;
  int p[2] ;
  pid_t pid ;
  if (pipecoe(p) < 0) return 0 ;
  pid = fork() ;
  if (pid < 0)
  {
    e = errno ;
    fd_close(p[1]) ;
    fd_close(p[0]) ;
    errno = e ;
    return 0 ;
  }
  if (pid)
  {
    fd_close(p[0]) ;
    pathexec_run(prog, argv, envp) ;
    e = errno ;
    fd_write(p[1], (char *)&e, sizeof(e)) ;
    _exit(127) ;
  }
  fd_close(p[1]) ;
  p[1] = fd_read(p[0], (char *)&e, sizeof(e)) ;
  if (p[1] < 0)
  {
    e = errno ;
    fd_close(p[0]) ;
    errno = e ;
    return 0 ;
  }
  fd_close(p[0]) ;
  if (p[1] == sizeof(e))
  {
    wait_pid(pid, &p[0]) ;
    errno = e ;
    return 0 ;
  }
  return pid ;
}

#endif
