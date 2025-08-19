/* ISC license. */

#include <skalibs/nonposix.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include <skalibs/bytestr.h>
#include <skalibs/env.h>
#include <skalibs/djbunix.h>

 /* XXX: breaks layering, but really openat() should be supported everywhere */
#include <skalibs/unix-transactional.h>

#define SUFFIX ":envdump:XXXXXX"

int env_dump4 (char const *dir, mode_t mode, char const *const *envp, int nochomp)
{
  int fd ;
  size_t dirlen = strlen(dir) ;
  char tmpdir[dirlen + sizeof(SUFFIX)] ;
  memcpy(tmpdir, dir, dirlen) ;
  memcpy(tmpdir + dirlen, SUFFIX, sizeof(SUFFIX)) ;
  if (!mkdtemp(tmpdir)) return 0 ;
  fd = open_read(tmpdir) ;
  if (fd == -1) goto err ;
  for (; *envp ; envp++)
  {
    size_t len = str_chr(*envp, '=') ;
    size_t vallen = strlen(*envp + len + 1) ;
    char fn[len + 1 + !nochomp] ;
    memcpy(fn, *envp, len) ;
    if (nochomp) fn[len] = 0 ;
    else { fn[len] = '\n' ; fn[len+1] = 0 ; }
    len = openwritenclose_at(fd, fn, *envp + len + 1 + !nochomp, vallen) ;
    if (len < vallen) goto cerr ;
  }
  fd_close(fd) ;
  if (chmod(tmpdir, mode) == -1) goto err ;
  if (rename(tmpdir, dir) == -1) goto err ;
  return 1 ;

 cerr:
  fd_close(fd) ;
 err:
  {
    int e = errno ;
    rm_rf(tmpdir) ;
    errno = e ;
  }
  return 0 ;
}
