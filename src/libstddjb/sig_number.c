/* ISC license. */

#include <strings.h>

#include <skalibs/sig.h>
#include "sig-internal.h"

int sig_number (char const *name)
{
  sigtable const *p = skalibs_sigtable ;
  for (; p->name ; p++) if (!strcasecmp(name, p->name)) break ;
  return p->number ;
}
