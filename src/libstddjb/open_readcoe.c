/* ISC license. */

#include <skalibs/nonposix.h>
#include <fcntl.h>
#include <skalibs/djbunix.h>

int open_readcoe (char const *fn)
{
  return open2(fn, O_RDONLY | O_NONBLOCK | O_CLOEXEC) ;
}
