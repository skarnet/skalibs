/* ISC license. */

/* MT-unsafe */

#include <skalibs/sysdeps.h>
#include <string.h>
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

#include <skalibs/sig.h>
#include <skalibs/strerr.h>
#include <skalibs/exec.h>

#endif

#include <skalibs/types.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/env.h>
#include <skalibs/djbunix.h>

 /*
    If n = 0 : child's stdin and stdout are the same as the parent's
    If n >= 1 : pipes between parent and child.
                Parent reads on even ones, writes on odd ones.
 */

pid_t child_spawn (char const *prog, char const *const *argv, char const *const *envp, int *fds, unsigned int n)
{
  pid_t pid ;
#ifdef SKALIBS_HASPOSIXSPAWN
  posix_spawn_file_actions_t actions ;
  posix_spawnattr_t attr ;
  int e ;
#else
  int syncpipe[2] ;
#endif
  int p[n ? n : 1][2] ;
  size_t m = sizeof(SKALIBS_CHILD_SPAWN_FDS_ENVVAR) ;
  unsigned int i = 0 ;
  char modifs[m + 1 + n * UINT_FMT] ;
  memcpy(modifs, SKALIBS_CHILD_SPAWN_FDS_ENVVAR "=", sizeof(SKALIBS_CHILD_SPAWN_FDS_ENVVAR)) ;
  for (; i < n ; i++)
  {
    if (pipe(p[i]) < 0) goto errpi ;
    if ((ndelay_on(p[i][i & 1]) < 0) || (coe(p[i][i & 1]) < 0))
    {
      i++ ; goto errpi ;
    }
  }
  for (i = 2 ; i < n ; i++)
  {
    m += uint_fmt(modifs + m, p[i][!(i & 1)]) ;
    if (i+1 < n) modifs[m++] = ',' ;
  }
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
  if (n >= 2 && p[1][0])
  {
    e = posix_spawn_file_actions_adddup2(&actions, p[1][0], 0) ;
    if (e) goto erractions ;
    e = posix_spawn_file_actions_addclose(&actions, p[1][0]) ;
    if (e) goto erractions ;
  }
  if (n && p[0][1] != 1)
  {
    e = posix_spawn_file_actions_adddup2(&actions, p[0][1], 1) ;
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
  if (pipecoe(syncpipe) < 0) goto errp ;

  pid = fork() ;
  if (pid < 0) goto errsp ;
  else if (!pid)
  {
    size_t len = strlen(PROG) ;
    char name[len + 9] ;
    memcpy(name, PROG, len) ;
    memcpy(name + len, " (child)", 9) ;
    PROG = name ;
    if (n >= 2)
    {
      if (fd_move2(0, p[1][0], 1, p[0][1]) < 0) goto syncdie ;
    }
    else if (n)
    {
      if (fd_move(1, p[0][1]) < 0) goto syncdie ;
    }
    sig_blocknone() ;
    mexec_aen(prog, argv, envp, modifs, m, 1) ;

  syncdie:
    {
      unsigned char c = errno ;
      fd_write(syncpipe[1], (char *)&c, 1) ;
    }
    _exit(127) ;
  }

  fd_close(syncpipe[1]) ;
  {
    unsigned char c ;
    syncpipe[1] = fd_read(syncpipe[0], (char *)&c, 1) ;
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

  for (i = n ; i ; i--)
  {
    fd_close(p[i-1][i & 1]) ;
    fds[i-1] = p[i-1][!(i & 1)] ;
  }
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
 errp:
#endif
  i = n ;
 errpi:
  while (i--)
  {
    fd_close(p[i][1]) ;
    fd_close(p[i][0]) ;
  }
  return 0 ;
}
