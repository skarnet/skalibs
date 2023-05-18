/* ISC license. */

#include <skalibs/djbunix.h>

int openslurpclose (stralloc *sa, char const *fn)
{
  return openslurpnclose(fn, sa, 0) ;
}
