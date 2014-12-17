/* ISC license. */

/* MT-unsafe */

#include <skalibs/stralloc.h>
#include <skalibs/skamisc.h>
#include <skalibs/djbunix.h>

int sarealpath (stralloc *sa, char const *path)
{
  return sarealpath_tmp(sa, path, &satmp) ;
}
