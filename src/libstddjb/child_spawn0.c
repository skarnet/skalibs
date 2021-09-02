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
  pid_t pid ;
  posix_spawnattr_t attr ;
  int e ;
  int nopath = !getenv("PATH") ;
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
  if (nopath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) < 0)) { e = errno ; goto errattr ; }
  e = posix_spawnp(&pid, prog, 0, &attr, (char *const *)argv, (char *const *)envp) ;
  if (nopath) unsetenv("PATH") ;
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
#include <skalibs/exec.h>

pid_t child_spawn0 (char const *prog, char const *const *argv, char const *const *envp)
{
  pid_t pid ;
  int p[2] ;
  unsigned char c ;
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
    exec_ae(prog, argv, envp) ;
    c = errno ;
    fd_write(p[1], (char *)&c, 1) ;
    _exit(127) ;
  }
  fd_close(p[1]) ;
  p[1] = fd_read(p[0], (char *)&c, 1) ;
  if (p[1] < 0)
  {
    fd_close(p[0]) ;
    return 0 ;
  }
  fd_close(p[0]) ;
  if (p[1])
  {
    wait_pid(pid, &p[0]) ;
    errno = c ;
    return 0 ;
  }
  return pid ;
}

#endif
