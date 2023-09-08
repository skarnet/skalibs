/* ISC license. */

/* MT-unsafe */

#include <skalibs/sysdeps.h>

#include <unistd.h>
#include <errno.h>

#include <skalibs/djbunix.h>

#ifdef SKALIBS_HASPOSIXSPAWN

#include <signal.h>
#include <stdlib.h>
#include <spawn.h>

#include <skalibs/config.h>

pid_t child_spawn2 (char const *prog, char const *const *argv, char const *const *envp, int *fds)
{
  pid_t pid ;
  posix_spawn_file_actions_t actions ;
  posix_spawnattr_t attr ;
  int p[2][2] ;
  int e ;
  int nopath = !getenv("PATH") ;
  sigset_t set ;
#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN
  int syncpipe[2] ;
  if (pipecoe(syncpipe) == -1) return 0 ;
#endif
  if (pipe(p[0]) == -1) goto err ;
  if (ndelay_on(p[0][0]) == -1 || coe(p[0][0]) == -1 || pipe(p[1]) == -1) goto errp ;
  if (ndelay_on(p[1][1]) == -1 || coe(p[1][1]) == -1) goto errp1 ;

  e = posix_spawnattr_init(&attr) ;
  if (e) goto erre ;
  sigemptyset(&set) ;
  e = posix_spawnattr_setsigmask(&attr, &set) ;
  if (e) goto errattr ;
  e = posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSIGMASK) ;
  if (e) goto errattr ;
  e = posix_spawn_file_actions_init(&actions) ;
  if (e) goto errattr ;
  if (p[1][0] != fds[0])
  {
    e = posix_spawn_file_actions_adddup2(&actions, p[1][0], fds[0]) ;
    if (e) goto erractions ;
    e = posix_spawn_file_actions_addclose(&actions, p[1][0]) ;
    if (e) goto erractions ;
  }
  if (p[0][1] != fds[1])
  {
    e = posix_spawn_file_actions_adddup2(&actions, p[0][1], fds[1]) ;
    if (e) goto erractions ;
    e = posix_spawn_file_actions_addclose(&actions, p[0][1]) ;
    if (e) goto erractions ;
  }
  if (nopath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) == -1))
  {
    e = errno ; goto erractions ;
  }
  e = posix_spawnp(&pid, prog, &actions, &attr, (char *const *)argv, (char *const *)envp) ;
  if (nopath) unsetenv("PATH") ;
  if (e) goto erractions ;

  posix_spawn_file_actions_destroy(&actions) ;
  posix_spawnattr_destroy(&attr) ;
  fd_close(p[0][1]) ;
  fd_close(p[1][0]) ;

#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN
  pid = child_spawn_workaround(pid, syncpipe) ;
  if (!pid)
  {
    fd_close(p[1][1]) ;
    fd_close(p[0][0]) ;
    return 0 ;
  }
#endif
  fds[0] = p[0][0] ;
  fds[1] = p[1][1] ;
  return pid ;

 erractions:
  posix_spawn_file_actions_destroy(&actions) ;
 errattr:
  posix_spawnattr_destroy(&attr) ;
 erre:
  errno = e ;
 errp1:
  fd_close(p[1][1]) ;
  fd_close(p[1][0]) ;
 errp:
  fd_close(p[0][1]) ;
  fd_close(p[0][0]) ;
 err:
#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN
  fd_close(syncpipe[1]) ;
  fd_close(syncpipe[0]) ;
#endif
  return 0 ;
}

#else

#include <skalibs/allreadwrite.h>
#include <skalibs/sig.h>
#include <skalibs/exec.h>

pid_t child_spawn2 (char const *prog, char const *const *argv, char const *const *envp, int *fds)
{
  pid_t pid ;
  int syncpipe[2] ;
  int p[2][2] ;
  char c ;

  if (pipe(p[0]) < 0) return 0 ;
  if (ndelay_on(p[0][0]) < 0 || coe(p[0][0]) < 0 || pipe(p[1]) < 0) goto errp ;
  if (ndelay_on(p[1][1]) < 0 || coe(p[1][1]) < 0) goto errp1 ;
  if (pipecoe(syncpipe) < 0) goto errp1 ;

  pid = fork() ;
  if (pid == -1) goto errsp ;
  else if (!pid)
  {
    if (fd_move2(fds[0], p[1][0], fds[1], p[0][1]) < 0) goto syncdie ;
    sig_blocknone() ;
    exec_ae(prog, argv, envp) ;
   syncdie:
    c = errno ;
    fd_write(syncpipe[1], &c, 1) ;
    _exit(127) ;
  }

  fd_close(syncpipe[1]) ;
  syncpipe[1] = fd_read(syncpipe[0], &c, 1) ;
  if (syncpipe[1])
  {
    int e = (unsigned char)c ;
    if (syncpipe[1] == -1) e = errno ;
    if (wait_pid(pid, &syncpipe[1]) == -1) e = errno ;
    errno = e ;
    goto errsp0 ;
  }
  fd_close(syncpipe[0]) ;
  fd_close(p[0][1]) ;
  fd_close(p[1][0]) ;

  fds[0] = p[0][0] ;
  fds[1] = p[1][1] ;
  return pid ;

 errsp:
  fd_close(syncpipe[1]) ;
 errsp0:
  fd_close(syncpipe[0]) ;
 errp1:
  fd_close(p[1][1]) ;
  fd_close(p[1][0]) ;
 errp:
  fd_close(p[0][1]) ;
  fd_close(p[0][0]) ;
  return 0 ;
}

#endif
