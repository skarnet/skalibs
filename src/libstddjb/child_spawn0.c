/* ISC license. */

#include <skalibs/sysdeps.h>
#include <errno.h>

#ifdef SKALIBS_HASPOSIXSPAWN

#include <signal.h>
#include <spawn.h>
#include <stdlib.h>
#include <skalibs/config.h>

pid_t child_spawn0 (char const *prog, char const *const *argv, char const *const *envp)
{
  posix_spawnattr_t attr ;
  int e ;
  pid_t pid ;
  int haspath = !!getenv("PATH") ;
  e = posix_spawnattr_init(&attr) ;
  if (e) goto err ;
  {
    sigset_t set ;
    sigemptyset(&set) ;
    e = posix_spawnattr_setsigmask(&attr, &set) ;
    if (e) goto errattr ;
    e = posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSIGMASK) ;
    if (e) goto errattr ;
  }
  if (!haspath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) < 0)) { e = errno ; goto errattr ; }
  e = posix_spawnp(&pid, prog, 0, &attr, (char *const *)argv, (char *const *)envp) ;
  if (!haspath) unsetenv("PATH") ;
  posix_spawnattr_destroy(&attr) ;
  if (e) goto err ;
  return pid ;

 errattr:
  posix_spawnattr_destroy(&attr) ;
 err:
  errno = e ;
  return 0 ;
}

#else

#include <unistd.h>
#include <string.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/strerr2.h>
#include <skalibs/sig.h>
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
    fd_close(p[1]) ;
    fd_close(p[0]) ;
    return 0 ;
  }
  if (!pid)
  {
    size_t len = strlen(PROG) ;
    char name[len + 9] ;
    memcpy(name, PROG, len) ;
    memcpy(name + len, " (child)", 9) ;
    PROG = name ;
    fd_close(p[0]) ;
    sig_blocknone() ;
    pathexec_run(prog, argv, envp) ;
    e = errno ;
    fd_write(p[1], (char *)&e, sizeof(e)) ;
    _exit(127) ;
  }
  fd_close(p[1]) ;
  p[1] = fd_read(p[0], (char *)&e, sizeof(e)) ;
  if (p[1] < 0)
  {
    fd_close(p[0]) ;
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
