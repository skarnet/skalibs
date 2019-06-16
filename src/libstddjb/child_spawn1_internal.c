/* ISC license. */

#include <skalibs/sysdeps.h>
#include <unistd.h>
#include <errno.h>

#ifdef SKALIBS_HASPOSIXSPAWN

#include <signal.h>
#include <spawn.h>
#include <stdlib.h>
#include <skalibs/config.h>
#include <skalibs/djbunix.h>

pid_t child_spawn1_internal (char const *prog, char const *const *argv, char const *const *envp, int *p, int to)
{
  posix_spawn_file_actions_t actions ;
  posix_spawnattr_t attr ;
  int e ;
  pid_t pid ;
  int haspath = !!getenv("PATH") ;
  if (coe(p[!(to & 1)]) < 0) { e = errno ; goto err ; }
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
  e = posix_spawn_file_actions_init(&actions) ;
  if (e) goto errattr ;
  if (p[to & 1] != to & 1)
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
  if (!haspath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) < 0)) { e = errno ; goto erractions ; }
  e = posix_spawnp(&pid, prog, &actions, &attr, (char *const *)argv, (char *const *)envp) ;
  if (!haspath) unsetenv("PATH") ;
  posix_spawn_file_actions_destroy(&actions) ;
  posix_spawnattr_destroy(&attr) ;
  fd_close(p[to & 1]) ;
  if (e) goto errp ;
  return pid ;

 erractions:
  posix_spawn_file_actions_destroy(&actions) ;
 errattr:
  posix_spawnattr_destroy(&attr) ;
 err:
  fd_close(p[to & 1]) ;
 errp:
  fd_close(p[!(to & 1)]) ;
  errno = e ;
  return 0 ;
}

#else

#include <string.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/strerr2.h>
#include <skalibs/sig.h>
#include <skalibs/djbunix.h>

pid_t child_spawn1_internal (char const *prog, char const *const *argv, char const *const *envp, int *p, int to)
{
  int e ;
  int syncp[2] ;
  pid_t pid ;
  if (coe(p[0]) < 0 || pipecoe(syncp) < 0)
  {
    fd_close(p[1]) ;
    fd_close(p[0]) ;
    return 0 ;
  }
  pid = fork() ;
  if (pid < 0)
  {
    fd_close(syncp[1]) ;
    fd_close(syncp[0]) ;
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
    fd_close(syncp[0]) ;
    fd_close(p[!(to & 1)]) ;
    if (fd_move(to & 1, p[to & 1]) < 0) goto err ;
    if ((to & 2) && (fd_copy(!(to & 1), to & 1) < 0)) goto err ;
    sig_blocknone() ;
    pathexec_run(prog, argv, envp) ;
   err:
    e = errno ;
    fd_write(syncp[1], (char *)&e, sizeof(e)) ;
    _exit(127) ;
  }
  fd_close(syncp[1]) ;
  fd_close(p[to & 1]) ;
  syncp[1] = fd_read(syncp[0], (char *)&e, sizeof(e)) ;
  if (syncp[1] < 0)
  {
    fd_close(syncp[0]) ;
    fd_close(p[!(to & 1)]) ;
    return 0 ;
  }
  fd_close(syncp[0]) ;
  if (syncp[1] == sizeof(e))
  {
    fd_close(p[!(to & 1)]) ;
    wait_pid(pid, &syncp[1]) ;
    errno = e ;
    return 0 ;
  }
  return pid ;
}

#endif
