/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/sig.h>
#include "sig-internal.h"

int sig_number (char const *name)
{
  register sigtable_t const *p = skalibs_sigtable ;
  for (; p->name ; p++) if (!str_diff(name, p->name)) break ;
  return p->number ;
}
