/* ISC license. */

/* MT-unsafe */

#include <skalibs/nonposix.h>
#include <unistd.h>
#include <grp.h>
#include <limits.h>
#include <skalibs/setgroups.h>
#include <skalibs/djbunix.h>

int prot_grps (char const *name)
{
  gid_t tab[NGROUPS_MAX] ;
  int n = prot_readgroups(name, tab, NGROUPS_MAX) ;
  return n < 0 ? -1 : setgroups(n, tab) ;
}
