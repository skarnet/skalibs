/* ISC license. */

/* MT-unsafe */

#include <skalibs/env.h>
#include <skalibs/djbunix.h>
#include <skalibs/posixplz.h>

void pathexec (char const *const *argv)
{
  pathexec_fromenv(argv, (char const **)environ, env_len((char const **)environ)) ;
}
