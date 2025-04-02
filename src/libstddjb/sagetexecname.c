/* ISC license. */

#include <skalibs/sysdeps.h>

#if defined(SKALIBS_PROCSELFEXE)

#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sagetexecname (stralloc *sa)
{
  return sareadlink(sa, SKALIBS_PROCSELFEXE) ;
}

#elif defined(SKALIBS_HASGETEXECNAME)

#include <skalibs/nonposix.h>
#include <stdlib.h>

#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sagetexecname (stralloc *sa)
{
  return sarealpath(sa, getexecname()) ;
}

#elif defined(SKALIBS_HASKERNPROCPATHNAME)

#include <skalibs/nonposix.h>
#ifdef __NetBSD__
#include <sys/param.h>
#endif
#include <limits.h>
#include <sys/sysctl.h>

#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sagetexecname (stralloc *sa)
{
  int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 } ;
  char buf[PATH_MAX] ;
  size_t len = sizeof(buf) ;
  if (sysctl(mib, 4, buf, &len, 0, 0) == -1) return -1 ;
  if (!stralloc_catb(sa, buf, len) || !stralloc_0(sa)) return -1 ;
  return 0 ;
}

#elif defined(SKALIBS_HAS_NSGETEXECUTABLEPATH)

#include <skalibs/nonposix.h>
#include <sys/types.h>
#include <stdint.h>
#include <macho-o/dyld.h>

#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sagetexecname (stralloc *sa)
{
  char buf[4096] ;
  uint32_t len = sizeof(buf) ;
  if (_NSGetExecutablePath(buf, &len) == -1) return -1 ;
  return sarealpath(sa, buf) ;
}

#elif defined(SKALIBS_HASGETAUXVAL)

#include <skalibs/nonposix.h>
#include <sys/auxv.h>

#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sagetexecname (stralloc *sa)
{
  unsigned long x = getauxval(AT_EXECFN) ;
  return sarealpath(sa, (char const *)x) ;
}

#elif defined(SKALIBS_HASDLADDR)

#include <skalibs/nonposix.h>
#include <dlfcn.h>

#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sagetexecname (stralloc *sa)
{
  Dl_info info ;
  if (!dladdr(&main, &info)) return -1 ;
  if (!stralloc_cats(sa, info.dli_fname) || !stralloc_0(sa)) return -1 ;
  return 0 ;
}

#else  /* we tried */

#include <errno.h>

#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sagetexecname (stralloc *sa)
{
  errno = ENOSYS ;
  return -1 ;
}

#endif
