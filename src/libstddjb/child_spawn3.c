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
#include <skalibs/sig.h>
#include <skalibs/strerr2.h>
#include <skalibs/exec.h>

#endif

#include <skalibs/types.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/env.h>
#include <skalibs/djbunix.h>

pid_t child_spawn3 (char const *prog, char const *const *argv, char const *const *envp, int *fds)
{
  pid_t pid ;
#ifdef SKALIBS_HASPOSIXSPAWN
  posix_spawn_file_actions_t actions ;
  posix_spawnattr_t attr ;
  int e ;
#else
  int syncpipe[2] ;
#endif
  int p[3][2] ;
  size_t m = sizeof(SKALIBS_CHILD_SPAWN_FDS_ENVVAR) ;
  char modifs[sizeof(SKALIBS_CHILD_SPAWN_FDS_ENVVAR) + UINT_FMT] = SKALIBS_CHILD_SPAWN_FDS_ENVVAR "=" ;
  if (pipe(p[0]) < 0 || ndelay_on(p[0][0]) < 0 || coe(p[0][0]) < 0) return 0 ;
  if (pipe(p[1]) < 0 || ndelay_on(p[1][1]) < 0 || coe(p[1][1]) < 0) goto errp0 ;
  if (pipe(p[2]) < 0 || ndelay_on(p[2][0]) < 0 || coe(p[2][0]) < 0) goto errp1 ;
  m += uint_fmt(modifs + sizeof(SKALIBS_CHILD_SPAWN_FDS_ENVVAR), p[2][1]) ;
  modifs[m++] = 0 ;

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
    size_t envlen = env_len(envp) ;
    char const *newenv[envlen + 2] ;
    if (!env_mergen(newenv, envlen+2, envp, envlen, modifs, m, 1)) goto erractions ;
    if (nopath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) < 0))
    {
      e = errno ; goto erractions ;
    }
    e = posix_spawnp(&pid, prog, &actions, &attr, (char *const *)argv, (char *const *)newenv) ;
    if (nopath) unsetenv("PATH") ;
    if (e) goto erractions ;
  }

  posix_spawn_file_actions_destroy(&actions) ;
  posix_spawnattr_destroy(&attr) ;

#else
  if (pipecoe(syncpipe) < 0) goto errp2 ;

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
    mexec_aen(prog, argv, envp, modifs, m, 1) ;

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

  fd_close(p[2][1]) ;
  fd_close(p[1][0]) ;
  fd_close(p[0][1]) ;
  fds[0] = p[0][0] ;
  fds[1] = p[1][1] ;
  fds[2] = p[2][0] ;
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
 errp2:
#endif
  fd_close(p[2][1]) ;
  fd_close(p[2][0]) ;
 errp1:
  fd_close(p[1][1]) ;
  fd_close(p[1][0]) ;
 errp0:
  fd_close(p[0][1]) ;
  fd_close(p[0][0]) ;
  return 0 ;
}
