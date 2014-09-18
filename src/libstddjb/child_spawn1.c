/* ISC license. */

#include <skalibs/sysdeps.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <skalibs/djbunix.h>

#ifdef SKALIBS_HASPOSIXSPAWN

#include <spawn.h>
#include <stdlib.h>
#include <skalibs/config.h>
#include <skalibs/env.h>

pid_t child_spawn1 (char const *prog, char const *const *argv, char const *const *envp, int *fd, int to)
{
  posix_spawn_file_actions_t actions ;
  int e ;
  int p[2] ;
  pid_t pid ;
  int haspath = !!env_get("PATH") ;
  if (pipe(p) < 0) return 0 ;
  to = !!to ;
  e = posix_spawn_file_actions_init(&actions) ;
  if (e) goto err ;
  e = posix_spawn_file_actions_addclose(&actions, p[!to]) ;
  if (e) goto erractions ;
  e = posix_spawn_file_actions_adddup2(&actions, p[to], to) ;
  if (e) goto erractions ;
  if (!haspath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) < 0)) { e = errno ; goto erractions ; }
  e = posix_spawnp(&pid, prog, &actions, 0, (char *const *)argv, (char *const *)envp) ;
  if (!haspath) unsetenv("PATH") ;
  posix_spawn_file_actions_destroy(&actions) ;
  fd_close(p[to]) ;
  if (e) goto errp ;
  *fd = p[!to] ;
  return pid ;

 erractions:
  posix_spawn_file_actions_destroy(&actions) ;
 err:
  fd_close(p[to]) ;
 errp:
  fd_close(p[!to]) ;
  errno = e ;
  return 0 ;
}

#else

#include <skalibs/allreadwrite.h>

pid_t child_spawn1 (char const *prog, char const *const *argv, char const *const *envp, int *fd, int to)
{
  int e ;
  int syncp[2] ;
  int p[2] ;
  pid_t pid ;
  if (pipe(p) < 0) return 0 ;
  if (pipecoe(syncp) < 0)
  {
    e = errno ;
    fd_close(p[1]) ;
    fd_close(p[0]) ;
    errno = e ;
    return 0 ;
  }
  to = !!to ;
  pid = fork() ;
  if (pid < 0)
  {
    e = errno ;
    fd_close(syncp[1]) ;
    fd_close(syncp[0]) ;
    fd_close(p[1]) ;
    fd_close(p[0]) ;
    errno = e ;
    return 0 ;
  }
  if (pid)
  {
    fd_close(syncp[0]) ;
    fd_close(p[!to]) ;
    if (fd_move(to, p[to]) < 0) goto err ;
    pathexec_run(prog, argv, envp) ;
err:
    e = errno ;
    fd_write(syncp[1], (char *)&e, sizeof(e)) ;
    _exit(127) ;
  }
  fd_close(syncp[1]) ;
  fd_close(p[to]) ;
  syncp[1] = fd_read(syncp[0], (char *)&e, sizeof(e)) ;
  if (syncp[1] < 0)
  {
    e = errno ;
    fd_close(syncp[0]) ;
    fd_close(p[!to]) ;
    errno = e ;
    return 0 ;
  }
  fd_close(syncp[0]) ;
  if (syncp[1] == sizeof(e))
  {
    fd_close(p[!to]) ;
    wait_pid(pid, &syncp[1]) ;
    errno = e ;
    return 0 ;
  }
  *fd = p[!to] ;
  return pid ;
}

#endif
