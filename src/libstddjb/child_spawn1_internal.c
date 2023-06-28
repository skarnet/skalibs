/* ISC license. */

#include <skalibs/sysdeps.h>

#include <errno.h>

#include <skalibs/djbunix.h>

#ifdef SKALIBS_HASPOSIXSPAWN

#include <signal.h>
#include <spawn.h>
#include <stdlib.h>

#include <skalibs/config.h>

#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN
# include "child_spawn-internal.h"
#endif

pid_t child_spawn1_internal (char const *prog, char const *const *argv, char const *const *envp, int *p, int to)
{
  pid_t pid ;
  posix_spawn_file_actions_t actions ;
  posix_spawnattr_t attr ;
  sigset_t set ;
  int e ;
  int nopath = !getenv("PATH") ;

#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN
  int syncpipe[2] ;
  if (pipecoe(syncpipe) == -1) goto err ;
#endif

  if (coe(p[!(to & 1)]) == -1) goto errp ;
  e = posix_spawnattr_init(&attr) ;
  if (e) goto erre ;
  sigemptyset(&set) ;
  e = posix_spawnattr_setsigmask(&attr, &set) ;
  if (e) goto errattr ;
  e = posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSIGMASK) ;
  if (e) goto errattr ;
  e = posix_spawn_file_actions_init(&actions) ;
  if (e) goto errattr ;
  if (p[to & 1] != (to & 1))
  {
    e = posix_spawn_file_actions_adddup2(&actions, p[to & 1], to & 1) ;
    if (e) goto erractions ;
    e = posix_spawn_file_actions_addclose(&actions, p[to & 1]) ;
    if (e) goto erractions ;
  }
  if (to & 2)
  {
    e = posix_spawn_file_actions_adddup2(&actions, to & 1, !(to & 1)) ;
    if (e) goto erractions ;
  }
  if (nopath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) < 0)) { e = errno ; goto erractions ; }
  e = posix_spawnp(&pid, prog, &actions, &attr, (char *const *)argv, (char *const *)envp) ;
  if (nopath) unsetenv("PATH") ;
  if (e) goto erractions ;

  posix_spawn_file_actions_destroy(&actions) ;
  posix_spawnattr_destroy(&attr) ;
  fd_close(p[to & 1]) ;

#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN
  return child_spawn_workaround(pid, syncpipe) ;
#else
  return pid ;
#endif

 erractions:
  posix_spawn_file_actions_destroy(&actions) ;
 errattr:
  posix_spawnattr_destroy(&attr) ;
 erre:
  errno = e ;
 errp:
#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN
  fd_close(syncpipe[1]) ;
  fd_close(syncpipe[0]) ;
 err:
#endif
  fd_close(p[1]) ;
  fd_close(p[0]) ;
  return 0 ;
}

#else

#include <unistd.h>

#include <skalibs/allreadwrite.h>
#include <skalibs/sig.h>
#include <skalibs/exec.h>

pid_t child_spawn1_internal (char const *prog, char const *const *argv, char const *const *envp, int *p, int to)
{
  pid_t pid ;
  int syncpipe[2] ;
  char c ;

  if (coe(p[0]) < 0 || pipecoe(syncpipe) < 0) goto err ;

  pid = fork() ;
  if (pid < 0) goto errsp ;
  if (!pid)
  {
    fd_close(p[!(to & 1)]) ;
    if (fd_move(to & 1, p[to & 1]) < 0) goto syncdie ;
    if ((to & 2) && (fd_copy(!(to & 1), to & 1) < 0)) goto syncdie ;
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
    if (wait_pid(pid, 0) == -1) e = errno ;
    errno = e ;
    goto errsp0 ;
  }
  fd_close(syncpipe[0]) ;
  fd_close(p[to & 1]) ;
  return pid ;

 errsp:
  fd_close(syncpipe[1]) ;
 errsp0:
  fd_close(syncpipe[0]) ;
 err:
  fd_close(p[1]) ;
  fd_close(p[0]) ;
  return 0 ;
}

#endif
