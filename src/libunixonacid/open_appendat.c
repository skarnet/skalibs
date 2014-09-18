/* ISC license. */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <skalibs/unix-transactional.h>

int open_appendat (int fd, char const *name)
{
  return open3_at(fd, name, O_WRONLY | O_NONBLOCK | O_APPEND | O_CREAT, 0666) ;
}
