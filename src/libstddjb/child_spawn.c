/* ISC license. */

/* MT-unsafe */

#include <skalibs/sysdeps.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/bytestr.h>
#include <skalibs/env.h>
#include <skalibs/djbunix.h>
#include <skalibs/uint.h>

#ifdef SKALIBS_HASPOSIXSPAWN

#include <stdlib.h>
#include <spawn.h>
#include <skalibs/config.h>

#else

#include <skalibs/sig.h>
#include <skalibs/strerr2.h>

#endif

#define NOFDVAR "SKALIBS_CHILD_SPAWN_FDS"


 /*
    If n = 0 : child's stdin and stdout are the same as the parent's
    If n >= 1 : pipes between parent and child.
                Parent reads on even ones, writes on odd ones.
 */

pid_t child_spawn (char const *prog, char const *const *argv, char const *const *envp, int *fds, unsigned int n)
{
#ifdef SKALIBS_HASPOSIXSPAWN
  posix_spawn_file_actions_t actions ;
  posix_spawnattr_t attr ;
#else
  int syncpipe[2] ;
#endif
  int p[n ? n : 1][2] ;
  pid_t pid ;
  int e ;
  unsigned int m = sizeof(NOFDVAR) ;
  unsigned int i = 0 ;
  char modifs[m + 1 + n * UINT_FMT] ;
  byte_copy(modifs, sizeof(NOFDVAR), NOFDVAR "=") ;
  for (; i < n ; i++) if (pipe(p[i]) < 0) { e = errno ; goto errp ; }
  for (i = 0 ; i < n ; i++)
    if ((ndelay_on(p[i][i & 1]) < 0) || (coe(p[i][i & 1]) < 0))
    {
      e = errno ; goto errp ;
    }
  for (i = 2 ; i < n ; i++)
  {
    m += uint_fmt(modifs + m, p[i][!(i & 1)]) ;
    if (i+1 < n) modifs[m++] = ',' ;
  }
  modifs[m++] = 0 ;

#ifdef SKALIBS_HASPOSIXSPAWN

  e = posix_spawnattr_init(&attr) ;
  if (e) goto errsp ;
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
  if (n >= 2)
  {
    e = posix_spawn_file_actions_adddup2(&actions, p[1][0], 0) ;
    if (e) goto erractions ;
    e = posix_spawn_file_actions_addclose(&actions, p[1][0]) ;
    if (e) goto erractions ;
  }
  if (n)
  {
    e = posix_spawn_file_actions_adddup2(&actions, p[0][1], 1) ;
    if (e) goto erractions ;
    e = posix_spawn_file_actions_addclose(&actions, p[0][1]) ;
    if (e) goto erractions ;
  }
  {
    int haspath = !!env_get("PATH") ;
    unsigned int envlen = env_len(envp) ;
    char const *newenv[envlen + 2] ;
    if (!env_merge(newenv, envlen+2, envp, envlen, modifs, m)) goto errsp ;
    if (!haspath && (setenv("PATH", SKALIBS_DEFAULTPATH, 0) < 0))
    {
      e = errno ; goto erractions ;
    }
    e = posix_spawnp(&pid, prog, &actions, &attr, (char *const *)argv, (char *const *)newenv) ;
    if (!haspath) unsetenv("PATH") ;
    if (e) goto erractions ;
  }

  posix_spawn_file_actions_destroy(&actions) ;
  posix_spawnattr_destroy(&attr) ;

#else
  if (pipe(syncpipe) < 0) { e = errno ; goto errp ; }
  if (coe(syncpipe[1]) < 0) { e = errno ; goto errsp ; }

  pid = fork() ;
  if (pid < 0) { e = errno ; goto errsp ; }
  else if (!pid)
  {
    unsigned int len = str_len(PROG) ;
    char name[len + 9] ;
    byte_copy(name, len, PROG) ;
    byte_copy(name + len, 9, " (child)") ;
    PROG = name ;
    fd_close(syncpipe[0]) ;
    if (n >= 2)
    {
      if (fd_move2(0, p[1][0], 1, p[0][1]) < 0) goto syncdie ;
    }
    else if (n)
    {
      if (fd_move(1, p[0][1]) < 0) goto syncdie ;
    }
    sig_blocknone() ;
    pathexec_r_name(prog, argv, envp, env_len(envp), modifs, m) ;

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
      if (syncpipe[1] < 0) e = errno ;
      else
      {
        kill(pid, SIGKILL) ;
        e = c ;
      }
      wait_pid(pid, &syncpipe[1]) ;
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
#endif
 errsp:
#ifndef SKALIBS_HASPOSIXSPAWN
  fd_close(syncpipe[1]) ;
 errsp0:
  fd_close(syncpipe[0]) ;
#endif
 errp:
  i = n ;
  while (i--)
  {
    fd_close(p[i][1]) ;
    fd_close(p[i][0]) ;
  }
  errno = e ;
  return 0 ;
}
