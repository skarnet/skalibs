/* ISC license. */

/* MT-unsafe */

#include <skalibs/skamisc.h>
#include <skalibs/djbunix.h>

char *realpath (char const *name, char *buf)
{
  return realpath_tmp(name, buf, &satmp) ;
}
