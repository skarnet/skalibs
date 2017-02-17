/* ISC license. */

#include <skalibs/sig.h>
#include "sig-internal.h"

char const *sig_name (int sig)
{
  sigtable_t const *p = skalibs_sigtable ;
  for (; p->number ; p++) if (sig == p->number) break ;
  return p->number ? p->name : "???" ;
}
