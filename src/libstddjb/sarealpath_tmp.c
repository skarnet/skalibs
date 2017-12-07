/* ISC license. */

/* This function is now obsolete. */

#include <skalibs/djbunix.h>

int sarealpath_tmp (stralloc *sa, char const *path, stralloc *tmp)
{
  (void)tmp ;
  return sarealpath(sa, path) ;
}
