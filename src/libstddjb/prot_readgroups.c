/* ISC license. */

/* MT-unsafe */

#include <sys/types.h>
#include <grp.h>
#include <errno.h>
#include <string.h>
#include <skalibs/djbunix.h>

int prot_readgroups (char const *name, gid_t *tab, unsigned int max)
{
  unsigned int n = 0 ;
  for (;;)
  {
    struct group *gr ;
    char **member ;
    errno = 0 ;
    if (n >= max) break ;
    gr = getgrent() ;
    if (!gr) break ;
    for (member = gr->gr_mem ; *member ; member++)
      if (!strcmp(name, *member)) break ;
    if (*member) tab[n++] = gr->gr_gid ;
  }
  endgrent() ;
  return errno ? -1 : n ;
}
