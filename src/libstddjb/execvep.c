/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/djbunix.h>

void execvep (char const *file, char const *const *argv, char const *const *envp, char const *path)
{
  if (!path) errno = EINVAL ;
  else if (file[str_chr(file, '/')])
    execve(file, (char *const *)argv, (char *const *)envp) ; /* execve prototype sucks */
  else
  {
    unsigned int pathlen = str_len(path) + 1 ;
    unsigned int filelen = str_len(file) ;
    int savederrno = 0 ;
    while (pathlen)
    {
      unsigned int split = byte_chr(path, pathlen - 1, ':') ;
      if (split)
      {
        char tmp[split + 2 + filelen] ;
        byte_copy(tmp, split, path) ;
        tmp[split] = '/' ;
        byte_copy(tmp + split + 1, filelen + 1, file) ;
        execve(tmp, (char *const *)argv, (char *const *)envp) ;
        if (errno != ENOENT)
        {
          savederrno = errno ;
          if ((errno != EACCES) && (errno != EPERM) && (errno != EISDIR)) break ;
        }
      }
      path += split+1 ; pathlen -= split+1 ;
    }
    if (savederrno) errno = savederrno ;
  }
}
