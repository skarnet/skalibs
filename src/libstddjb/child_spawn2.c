/* ISC license. */

/* MT-unsafe */

#include <skalibs/sysdeps.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#ifdef SKALIBS_HASPOSIXSPAWN

#include <stdlib.h>
#include <spawn.h>
#include <skalibs/config.h>

#else

#include <string.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/sig.h>
#include <skalibs/strerr2.h>
#include <skalibs/exec.h>

#endif

#include <skalibs/djbunix.h>

pid_t child_spawn2 (char const *prog, char const *const *argv, char const *const *envp, int *fds)
{
  pid_t pid ;
#ifdef SKALIBS_HASPOSIXSPAWN
  posix_spawn_file_actions_t actions ;
  posix_spawnattr_t attr ;
  int e ;
#else
  int syncpipe[2] ;
#endif
  int p[2][2] ;
  if (pipe(p[0]) < 0) return 0 ;
  if (ndelay_on(p[0][0]) < 0 || coe(p[0][0]) < 0 || pipe(p[1]) < 0) goto errp ;
  if (ndelay_on(p[1][1]) < 0 || coe(p[1][1]) < 0) goto errp1 ;

#ifdef SKALIBS_HASPOSIXSPAWN

  e = posix_spawnattr_init(&attr) ;
  if (e) goto erre ;
  {
    sigset_t set ;
    sigemptyset(&set) ;
    e = posix_spawnattr_setsigmask(&attr, &set) ;
    if (e) goto errattr ;
    e = posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSIGMASK) ;
    if (e) goto errattr ;
  }
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
  {
    int nopath = !getenv("PATH") ;
    if (nopath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) < 0))
    {
      e = errno ; goto erractions ;
    }
    e = posix_spawnp(&pid, prog, &actions, &attr, (char *const *)argv, (char *const *)envp) ;
    if (nopath) unsetenv("PATH") ;
    if (e) goto erractions ;
  }

  posix_spawn_file_actions_destroy(&actions) ;
  posix_spawnattr_destroy(&attr) ;

#else
  if (pipecoe(syncpipe) < 0) goto errp1 ;

  pid = fork() ;
  if (pid < 0) goto errsp ;
  else if (!pid)
  {
    size_t len = strlen(PROG) ;
    char name[len + 9] ;
    memcpy(name, PROG, len) ;
    memcpy(name + len, " (child)", 9) ;
    PROG = name ;
    if (fd_move2(fds[0], p[1][0], fds[1], p[0][1]) < 0) goto syncdie ;
    sig_blocknone() ;
    exec_ae(prog, argv, envp) ;

  syncdie:
    {
      char c = errno ;
      fd_write(syncpipe[1], &c, 1) ;
    }
    _exit(127) ;
  }

  fd_close(syncpipe[1]) ;
  {
    char c ;
    syncpipe[1] = fd_read(syncpipe[0], &c, 1) ;
    if (syncpipe[1])
    {
      int e = c ;
      if (syncpipe[1] < 0) e = errno ;
      if (wait_pid(pid, &syncpipe[1]) < 0) e = errno ;
      errno = e ;
      goto errsp0 ;
    }
  }
  fd_close(syncpipe[0]) ;
#endif

  fd_close(p[0][1]) ; fds[0] = p[0][0] ;
  fd_close(p[1][0]) ; fds[1] = p[1][1] ;
  return pid ;

#ifdef SKALIBS_HASPOSIXSPAWN
 erractions:
  posix_spawn_file_actions_destroy(&actions) ;
 errattr:
  posix_spawnattr_destroy(&attr) ;
 erre:
  errno = e ;
#endif
#ifndef SKALIBS_HASPOSIXSPAWN
 errsp:
  fd_close(syncpipe[1]) ;
 errsp0:
  fd_close(syncpipe[0]) ;
#endif
 errp1:
  fd_close(p[1][1]) ;
  fd_close(p[1][0]) ;
 errp:
  fd_close(p[0][1]) ;
  fd_close(p[0][0]) ;
  return 0 ;
}
