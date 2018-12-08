/* ISC license. */

#include <sys/stat.h>

#include <skalibs/djbunix.h>
#include <skalibs/posixplz.h>

static int f (char const *fn, mode_t mode, void *data)
{
  int r = mkfifo(fn, mode) ;
  if (r == -1) return -1 ;
  r = open_readb(fn) ;
  if (r == -1) unlink_void(fn) ;
  return r ;
}

int mkptemp (char *s)
{
  return mkfiletemp(s, &f, 0600, 0) ;
}
