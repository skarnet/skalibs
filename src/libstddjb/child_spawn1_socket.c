/* ISC license. */

#include <skalibs/webipc.h>
#include <skalibs/djbunix.h>
#include "djbunix-internal.h"

pid_t child_spawn1_socket (char const *prog, char const *const *argv, char const *const *envp, int *fd)
{
  pid_t pid ;
  int p[2] ;
  if (ipc_pair_b(p) < 0) return 0 ;
  pid = child_spawn1_internal(prog, argv, envp, p, 1) ;
  if (!pid) return 0 ;
  *fd = p[0] ;
  return pid ;
}
