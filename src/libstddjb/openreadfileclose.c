/* ISC license. */

#include <sys/stat.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int openreadfileclose (char const *file, stralloc *sa, size_t limit)
{
  size_t n ;
  int fd = openbc_read(file) ;
  if (fd < 0) return 0 ;
  {
    struct stat st ;
    if (fstat(fd, &st) < 0) goto err ;
    n = st.st_size ;
  }
  if (limit && (limit < n)) n = limit ;
  if (!stralloc_ready_tuned(sa, sa->len + n, 0, 0, 1)) goto err ;
  {
    size_t r = allread(fd, sa->s + sa->len, n) ;
    sa->len += r ;
    if (r < n) goto err ;
  }
  fd_close(fd) ;
  return 1 ;

err:
  fd_close(fd) ;
  return 0 ;
}
