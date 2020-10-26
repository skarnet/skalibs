/* ISC license. */

#include <skalibs/nonposix.h>
#include <fcntl.h>
#include <skalibs/djbunix.h>

int open_writecoe (char const *fn)
{
  return open2(fn, O_WRONLY | O_NONBLOCK | O_CLOEXEC) ;
}
