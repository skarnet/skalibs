/* ISC license. */

#include <skalibs/sysdeps.h>

#include <errno.h>

#ifdef SKALIBS_HASPOSIXSPAWN

#include <signal.h>
#include <stdlib.h>
#include <spawn.h>

#include <skalibs/config.h>
#include <skalibs/djbunix.h>

pid_t child_spawn0 (char const *prog, char const *const *argv, char const *const *envp)
{
  pid_t pid ;
  posix_spawnattr_t attr ;
  sigset_t set ;
  int e ;
  int nopath = !getenv("PATH") ;
#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN
  int p[2] ;
  if (pipecoe(p) == -1) return 0 ;
#endif
  e = posix_spawnattr_init(&attr) ;
  if (e) goto err ;
  sigemptyset(&set) ;
  e = posix_spawnattr_setsigmask(&attr, &set) ;
  if (e) goto errattr ;
  e = posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSIGMASK) ;
  if (e) goto errattr ;
  if (nopath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) < 0)) { e = errno ; goto errattr ; }
  e = posix_spawnp(&pid, prog, 0, &attr, (char *const *)argv, (char *const *)envp) ;
  if (nopath) unsetenv("PATH") ;
  if (e) goto errattr ;

  posix_spawnattr_destroy(&attr) ;
#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN
  return child_spawn_workaround(pid, p) ;
#else
  return pid ;
#endif

 errattr:
  posix_spawnattr_destroy(&attr) ;
 err:
#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN
  fd_close(p[1]) ;
  fd_close(p[0]) ;
#endif
  errno = e ;
  return 0 ;
}

#else

#include <unistd.h>

#include <skalibs/allreadwrite.h>
#include <skalibs/sig.h>
#include <skalibs/djbunix.h>
#include <skalibs/exec.h>

pid_t child_spawn0 (char const *prog, char const *const *argv, char const *const *envp)
{
  pid_t pid ;
  int p[2] ;
  char c ;

  if (pipecoe(p) == -1) return 0 ;
  pid = fork() ;
  if (pid < 0)
  {
    fd_close(p[1]) ;
    fd_close(p[0]) ;
    return 0 ;
  }
  if (!pid)
  {
    sig_blocknone() ;
    exec_ae(prog, argv, envp) ;
    c = errno ;
    fd_write(p[1], &c, 1) ;
    _exit(127) ;
  }
  fd_close(p[1]) ;
  p[1] = fd_read(p[0], &c, 1) ;
  if (p[1] < 0)
  {
    fd_close(p[0]) ;
    return 0 ;
  }
  fd_close(p[0]) ;
  if (p[1])
  {
    wait_pid(pid, &p[0]) ;
    errno = (unsigned char)c ;
    return 0 ;
  }
  return pid ;
}

#endif
