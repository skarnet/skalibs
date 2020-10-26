/* ISC license. */

#include <skalibs/nonposix.h>
#include <fcntl.h>
#include <skalibs/djbunix.h>

int openb_readcoe (char const *fn)
{
  return open2(fn, O_RDONLY | O_CLOEXEC) ;
}
