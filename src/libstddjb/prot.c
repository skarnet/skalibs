/* ISC license. */

/* MT-unsafe */

#include <unistd.h>
#include <pwd.h>
#include <errno.h>
#include <skalibs/djbunix.h>

int prot_setuidgid (char const *name)
{
  struct passwd *pw = getpwnam(name) ;
  if (!pw)
  {
    if (!errno) errno = ESRCH ;
    return 0 ;
  }
  return !prot_grps(name) && !setgid(pw->pw_gid) && !setuid(pw->pw_uid) ;
}
