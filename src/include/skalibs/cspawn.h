/* ISC license. */

#ifndef SKALIBS_CSPAWN_H
#define SKALIBS_CSPAWN_H

#include <sys/types.h>
#include <stdint.h>

#define CSPAWN_FLAGS_SELFPIPE_FINISH 0x0001U
#define CSPAWN_FLAGS_SIGBLOCKNONE 0x0002U
#define CSPAWN_FLAGS_SETSID 0x0004U

enum cspawn_fileaction_type_e
{
  CSPAWN_FA_CLOSE,
  CSPAWN_FA_COPY,
  CSPAWN_FA_MOVE,
  CSPAWN_FA_OPEN,
  CSPAWN_FA_CHDIR,
  CSPAWN_FA_FCHDIR
} ;

struct cspawn_fa_openinfo_s
{
  int fd ;
  char const *file ;
  int oflag ;
  mode_t mode ;
} ;

union cspawn_fileaction_u
{
  int fd ;
  int fd2[2] ;
  char const *path ;
  struct cspawn_fa_openinfo_s openinfo ;
} ;

typedef struct cspawn_fileaction_s cspawn_fileaction, *cspawn_fileaction_ref ;
struct cspawn_fileaction_s
{
  enum cspawn_fileaction_type_e type ;
  union cspawn_fileaction_u x ;
} ;


 /* Generic interface for posix_spawn() with a fork()+execve() fallback */

extern pid_t cspawn (char const *, char const *const *, char const *const *, uint16_t, cspawn_fileaction const *, size_t) ;


 /* Simple spawn functions with 0 or 1 communicating fds. */

extern pid_t child_spawn0 (char const *, char const *const *, char const *const *) ;
extern pid_t child_spawn1_pipe (char const *, char const *const *, char const *const *, int *, int) ;
extern pid_t child_spawn1_socket (char const *, char const *const *, char const *const *, int *) ;


 /*
    Spawn function with 2 communicating pipes. The int * points to 2 fds.
    Input: fds[0] and fds[1] are the fds to move the pipes to in the child.
    Output: fds[0] and fds[1] contain the pipes to the child.
 */

extern pid_t child_spawn2 (char const *, char const *const *, char const *const *, int *) ;


 /*
    Same, with an additional pipe from the child to the parent.
    The int * points to 3 fds.
    The additional fd# is available to the child in the defined env variable.
 */

#define SKALIBS_CHILD_SPAWN_FDS_ENVVAR "SKALIBS_CHILD_SPAWN_FDS"

extern pid_t child_spawn3 (char const *, char const *const *, char const *const *, int *) ;


 /*
    Generalization of the previous functions.
    * requests n (the last arg) communication fds between parent and child. Uses pipes.
    * if n=1, equivalent to child_spawn1_pipe; child writes, parent reads.
    * if n>=2, parent reads on even and writes on odd.
 */

extern pid_t child_spawn (char const *, char const *const *, char const *const *, int *, size_t) ;


 /* cspawn, but running as a grandchild. Uses one fork(). */

extern pid_t gcspawn (char const *, char const *const *, char const *const *, uint16_t, cspawn_fileaction const *, size_t) ;

#endif
