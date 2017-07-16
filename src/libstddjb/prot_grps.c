/* ISC license. */

/* MT-unsafe */

#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>
#include <errno.h>
#include <skalibs/setgroups.h>
#include <skalibs/djbunix.h>

int prot_grps (char const *name)
{
  gid_t tab[NGROUPS_MAX] ;
  struct passwd *pw ;
  int n = prot_readgroups(name, tab, NGROUPS_MAX) ;
  if (n < 0) return n ;
  errno = 0 ;
  pw = getpwnam(name) ;
  if (!pw)
  {
    if (!errno) errno = ENOENT ;
    return -1 ;
  }
  return setgroups_and_gid(pw->pw_gid, n, tab) ;
}
